#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class ServerConnection : public QObject
{
    Q_OBJECT
signals:
    void connected();
    void disconnected();
    void dataRead(QString);

public:
    using reply_handler = std::function<void(const QByteArray&)>;
    ServerConnection();
    ServerConnection(const QString& h, unsigned short p, const QString& pwd);
    ~ServerConnection();

    void setHost(const QString& h)
    { host = h; }

    void setPassword(const QString& p)
    { password = p; }

    void setPort(unsigned short p)
    { port = p; }

    bool isConnected() const
    { return is_connected; }

    void connectToHost();

    void onReadTcpData();

    void onDisconnected();

    void sendMessage(const QString& msg, reply_handler reply);
    void sendSimpleMessage(const QString& msg);
private:
    QTcpSocket *connection;
    reply_handler current_reply_handler;

    unsigned short port;
    QString host;
    QString password;

    bool is_connected;

    const QString SERVER_OK_REPLY{"welcome!"};
};

#endif // SERVERCONNECTION_H
