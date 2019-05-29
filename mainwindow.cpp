/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

#include "menuwidget.h"
#include "connectscreen.h"
#include "commandscreen.h"
#include "remotemousescreen.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    QPixmap bkgn(":/images/bgn.png");
    QPixmap bgnc(":/images/bgnc.png");
    bkgn.scaled(this->size());
    bgnc.scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgn);
    QPalette connected_palette;
    connected_palette.setBrush(QPalette::Background, bgnc);
    this->setPalette(palette);

    connection = new ServerConnection();
    connect(connection, &ServerConnection::connected, [this]() { this->onConnected(); });

    layout = new QHBoxLayout(this);
    menu_widget = new MenuWidget(connection, this);

    auto connection_label = new QLabel("Disconnected");
    QString connected_label_style = "QLabel { background-color : green; color : black; }";
    QString disconnected_label_style = "QLabel { background-color : red; color : black; }";
    connection_label->setStyleSheet(disconnected_label_style);
    connection_label->setFixedHeight(80);
    QFont f("Arial", 14, QFont::Bold);
    connection_label->setFont(f);
    connection_label->setAlignment(Qt::AlignCenter);
    menu_widget->addToMenu(connection_label);
    connect(connection, &ServerConnection::connected, [this, connection_label, connected_label_style, connected_palette](){
        connection_label->setStyleSheet(connected_label_style);
        connection_label->setText("Connected");
        this->setPalette(connected_palette);
    });
    connect(connection, &ServerConnection::disconnected, [this, connection_label, disconnected_label_style, palette](){
       connection_label->setStyleSheet(disconnected_label_style);
       connection_label->setText("Disconnected");
       this->setPalette(palette);
    });

    widget->setLayout(layout);
    layout->addWidget(menu_widget);
    current_screen = menu_widget;
    connect(menu_widget, &Screen::pushScreen, this, [this](Screen *scr){ pushScreen(scr); });

    auto connect_button = menu_widget->createPushButton("Connect", [mw = menu_widget, this](){ mw->pushScreen(new ConnectScreen(this->connection, this)); });
    connect(connection, &ServerConnection::connected, connect_button, [connect_button](){ connect_button->setEnabled(false); });
    connect(connection, &ServerConnection::disconnected, connect_button, [connect_button](){ connect_button->setEnabled(true); });
    menu_widget->addToMenu(connect_button);

    auto remote_button = menu_widget->createPushButton("Remote control", [mw = menu_widget, this](){ mw->pushScreen(new RemoteMouseScreen(this)); });
    menu_widget->addToMenu(remote_button);
    remote_button->setEnabled(false);
    connect(connection, &ServerConnection::connected, [remote_button](){ remote_button->setEnabled(true); });
    connect(connection, &ServerConnection::disconnected, [remote_button](){ remote_button->setEnabled(false); });

    auto commands_button = menu_widget->createPushButton("Commands", [mw = menu_widget, this](){ mw->pushScreen(new CommandScreen(this->command_list, this->connection, this)); });
    commands_button->setEnabled(false);
    menu_widget->addToMenu(commands_button);
    connect(connection, &ServerConnection::connected, [commands_button](){ commands_button->setEnabled(true); });
    connect(connection, &ServerConnection::disconnected, [commands_button](){ commands_button->setEnabled(false); });

    auto disconnect_button = menu_widget->createPushButton("Disconnect", [conn = this->connection](){
       conn->disconnectFromHost();
    });
    disconnect_button->setEnabled(false);
    connect(connection, &ServerConnection::connected, disconnect_button, [disconnect_button](){ disconnect_button->setEnabled(true); });
    connect(connection, &ServerConnection::disconnected, disconnect_button, [disconnect_button](){ disconnect_button->setEnabled(false); });
    menu_widget->addToMenu(disconnect_button);

    connect(connection, &ServerConnection::disconnected, this, [this](){ command_list.clear(); });
    connect(connection, &ServerConnection::disconnected, this, [this](){ this->pushScreen(menu_widget); });

    auto exit_button = menu_widget->createPushButton("Exit", [](){
        QApplication::quit();
    });
    menu_widget->addToMenu(exit_button);
}

void MainWindow::onConnected()
{
    connection->sendMessage("list_commands", [this](const QByteArray& data) {
        this->onListCommands(data);
    });
}

void MainWindow::onListCommands(const QByteArray & data)
{
    auto commands = QString::fromUtf8(data);
    std::string cmd_string = commands.toStdString();
    auto split_commands = commands.split("'");

    for( int i = 1; i < split_commands.size(); i+=2 )
    {
        command_list.push_back(std::move(split_commands.at(i)));
    }
}

void MainWindow::pushScreen(Screen *new_screen, bool is_overlapping)
{
    layout->removeWidget(current_screen);
    if( is_overlapping ) {
        overlapped_screen.push_back(current_screen);
    }
    else {
        if(current_screen != menu_widget)
            current_screen->deleteLater();
        else {
            for( auto screen : overlapped_screen )
            {
                screen->deleteLater();
            }
            overlapped_screen.clear();
        }
    }
    current_screen->hide();


    if(new_screen != menu_widget) {
        connect(new_screen, &Screen::pushScreen, this, [this](Screen *scr){ pushScreen(scr); });
        connect(new_screen, &Screen::pushOverlappingScreen, [this](Screen *scr){ pushScreen(scr, true); });
        connect(new_screen, &Screen::showOverlappedScreen, [this](){ showOverlappedScreen(); });
        connect(new_screen, &Screen::backToMenu, this, [this](){ pushScreen(this->menu_widget); });
        connect(new_screen, &Screen::sendData, this, [this](const QByteArray& data){ this->connection->sendSimpleMessage(data); });
        connect(new_screen, &Screen::showMouse, this, [this](){ pushScreen(new RemoteMouseScreen(this)); });
    }
    current_screen = new_screen;
    layout->addWidget(new_screen);
    new_screen->show();
}

void MainWindow::showOverlappedScreen()
{
    if(overlapped_screen.empty()) return;

    layout->removeWidget(current_screen);
    if(current_screen != menu_widget)
        current_screen->deleteLater();
    current_screen->hide();

    current_screen = overlapped_screen.back();
    overlapped_screen.pop_back();
    layout->addWidget(current_screen);
    current_screen->show();
}

