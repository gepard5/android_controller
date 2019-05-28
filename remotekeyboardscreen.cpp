#include "remotekeyboardscreen.h"
#include <iostream>

#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "keyreceiver.h"

#include <QLineEdit>

RemoteKeyboardScreen::RemoteKeyboardScreen(QWidget * parent) : Screen(parent)
{
    auto text_edit = new QLineEdit();
    auto keyboard_layout = new QVBoxLayout();
    main_layout->addLayout(keyboard_layout);
    auto send_button = createPushButton("send text", [this, text_edit](){
       auto txt = text_edit->text();
       emit sendData(QString("print " + txt).toUtf8());
       text_edit->setText("");
    });
    keyboard_layout->addWidget(text_edit);
    keyboard_layout->addWidget(send_button);
    auto enter_button = createKeyboardButton("Enter", "enter");
    keyboard_layout->addWidget(enter_button);
    auto backspace_button = createKeyboardButton("Backspace", "backspace");
    keyboard_layout->addWidget(backspace_button);
    auto delete_button = createKeyboardButton("Delete", "delete");
    keyboard_layout->addWidget(delete_button);
}

void RemoteKeyboardScreen::showKeyboard()
{
    keyboard->show();
   // keypress->show();
   // keypress->setFocusPolicy(Qt::StrongFocus);
}

QPushButton *RemoteKeyboardScreen::createKeyboardButton(const QString& key, const QString& msg)
{
    auto button = new QPushButton(key);
    connect(button, &QPushButton::clicked, this, [this, msg](){
       emit sendData((QString("keyboard ") + msg).toUtf8());
    });
    return button;
}
