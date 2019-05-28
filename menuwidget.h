#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "screen.h"
#include "serverconnection.h"

class MenuWidget : public Screen
{
    Q_OBJECT
public:
    explicit MenuWidget(ServerConnection *conn, QWidget *parent = nullptr);

    void addToMenu(QWidget* widg);


private:
};

#endif // MENUWIDGET_H
