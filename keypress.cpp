#include "keypress.h"
#include <iostream>

#include <QVBoxLayout>
#include <QKeyEvent>

KeyPress::KeyPress(QWidget * parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout();
    setLayout(layout);
}

void KeyPress::keyPressEvent(QKeyEvent *event)
{
    int key_code = event->key();
    const std::map<int, QString> special_keys = {
        { Qt::Key_Enter, "enter"},
        { Qt::Key_Backspace, "backspace" },
        { Qt::Key_Escape, "esc" }
    };
    QString key;
    if( special_keys.find(key_code) != special_keys.end()) {
        key = special_keys.at(key_code);
    }
    else {
        key = event->text();
    }
    std::cout<<"keypressed"<<std::endl;
    emit keyPressed(key);
}
