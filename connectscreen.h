#ifndef CONNECTSCREEN_H
#define CONNECTSCREEN_H

#include "screen.h"
#include "serverconnection.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>


class ConnectScreen : public Screen
{
signals:
    void connected();

public:
    ConnectScreen(ServerConnection *c, QWidget *parent);

	bool connectTcp();

protected:
    void onReadTcpData() {}

private:
    QPushButton* connect_button;
    QPushButton* options_button;

    QLineEdit *host_edit;
    QLineEdit *password_edit;
    QLineEdit *port_edit;

    ServerConnection *connection;
};

#endif // CONNECTSCREEN_H
