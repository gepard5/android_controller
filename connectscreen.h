#ifndef CONNECTSCREEN_H
#define CONNECTSCREEN_H

#include "screen.h"
#include "serverconnection.h"
#include "location.h"

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
    ~ConnectScreen();

	bool connectTcp();

protected:
    void onReadTcpData() {}
    void setFieldsFromLocation(const QString& l);

    void readLocationsFromFile();
    void writeLocationsToFile();

private:
    QPushButton* connect_button;
    QPushButton* options_button;

    QLineEdit *host_edit;
    QLineEdit *password_edit;
    QLineEdit *port_edit;

    ServerConnection *connection;
    std::map<QString, Location> locations_map;
    QString current_location;
};

#endif // CONNECTSCREEN_H
