#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <functional>

class Command : public QObject
{
    Q_OBJECT

signals:
    void sendData(QString);

public:
    Command();
    ~Command() = default;
    void fromQString(const QString&);

    void setAction(std::function<void()> act)
    { action = act; }

    void launch()
    { action(); }

private:
    std::function<void()> action;
};

#endif // COMMAND_H
