#ifndef REMOTEKEYBOARDSCREEN_H
#define REMOTEKEYBOARDSCREEN_H

#include "screen.h"

#include <QPushButton>
#include <QInputMethod>
#include "keypress.h"

class RemoteKeyboardScreen : public Screen
{
public:
    RemoteKeyboardScreen(QWidget* parent);

protected:
    void showKeyboard();

    QPushButton *createKeyboardButton(const QString& key, const QString& msg = "");

    QPushButton *show_keyboard;
    QInputMethod *keyboard;
    KeyPress *keypress;
};

#endif // REMOTEKEYBOARDSCREEN_H
