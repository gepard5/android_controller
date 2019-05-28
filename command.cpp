#include "command.h"

Command::Command() : QObject (nullptr)
{

}

void Command::fromQString(const QString& command)
{
    setAction([this, command](){
        emit sendData(command);
    });
}

