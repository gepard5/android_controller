#include "menuwidget.h"

#include "connectscreen.h"

MenuWidget::MenuWidget(ServerConnection *conn, QWidget *parent) : Screen(parent, false)
{

}

void MenuWidget::addToMenu(QWidget *widg)
{
    main_layout->addWidget(widg);
}
