#ifndef COMMANDSCREEN_H
#define COMMANDSCREEN_H

#include <functional>

#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>

#include "screen.h"
#include "serverconnection.h"
#include "command.h"


class CommandScreen : public Screen
{
signals:
    void sendData(QString);

public:
    CommandScreen();
    CommandScreen(const std::vector<QString>& commands, ServerConnection * conn, QWidget * parent);



private:
    QVBoxLayout *commands_layout;
    std::vector<QPushButton*> commands_list;
    ServerConnection *connection;
};

#endif // COMMANDSCREEN_H
