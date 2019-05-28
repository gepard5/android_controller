#include "serverconnection.h"

#include <iostream>
#include <QMessageBox>

ServerConnection::ServerConnection()
{
    host = "127.0.0.1";
    port = 9999;
    password = "password";
    connection = nullptr;
}

ServerConnection::ServerConnection(const QString& h, unsigned short p, const QString& pwd)
{
    host = h;
    port = p;
    password = pwd;
    connection = nullptr;
}

ServerConnection::~ServerConnection()
{
    if(connection) connection->deleteLater();
}

void ServerConnection::onDisconnected()
{
    std::cout<<"Disconnected"<<std::endl;
    is_connected = false;
    connection->deleteLater();
    connection = nullptr;
    emit disconnected();
}

void ServerConnection::onReadTcpData()
{
    QByteArray data = connection->readAll();

    auto tmp_handler = current_reply_handler;
    current_reply_handler = [this](const QByteArray& data){ emit dataRead(QString::fromUtf8(data)); };
    tmp_handler(data);
}

void ServerConnection::sendMessage(const QString & msg, reply_handler reply)
{
    current_reply_handler = reply;
    connection->write((msg+QString("#####")).toUtf8());
}

void ServerConnection::sendSimpleMessage(const QString &msg)
{
    return sendMessage(msg,[this](const QByteArray& data) {
       emit dataRead(QString::fromUtf8(data));
    });
}

void ServerConnection::connectToHost()
{
    if(connection) {
        connection->deleteLater();
    }
    connection = new QTcpSocket();
    is_connected = false;

    connect(connection, &QTcpSocket::readyRead, [this](){ this->onReadTcpData(); });
    connect(connection, &QTcpSocket::disconnected, [this](){ this->onDisconnected(); });
    connection->connectToHost(host, port);
    if(connection->waitForConnected()) {
        std::cout<<"Connected!"<<std::endl;
        auto correct_pwd = SERVER_OK_REPLY;
        sendMessage(password, [this, correct_pwd](const QByteArray& data) {
            QString reply = QString::fromUtf8(data).trimmed();
            if(reply == SERVER_OK_REPLY) {
                emit connected();
                is_connected = true;
            }
        });
    }
    else {
        QMessageBox *popup = new QMessageBox(QMessageBox::Warning, "Failed to connect", "Failed to connect to server. Check your settings");
        popup->exec();
        popup->deleteLater();
    }
}
