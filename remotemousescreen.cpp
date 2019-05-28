#include "remotemousescreen.h"
#include <iostream>
#include "touchpad.h"
#include "scrollbar.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QLineEdit>

RemoteMouseScreen::RemoteMouseScreen(QWidget * parent) : Screen(parent)
{
    mouse_layout = new QVBoxLayout();

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
    auto control_widget = new QWidget();
    auto control_layout = new QHBoxLayout();
    control_widget->setLayout(control_layout);
    auto enter_button = createKeyboardButton("Enter", "enter");
    control_layout->addWidget(enter_button);
    auto backspace_button = createKeyboardButton("Backspace", "backspace");
    control_layout->addWidget(backspace_button);
    auto delete_button = createKeyboardButton("Delete", "delete");
    control_layout->addWidget(delete_button);
    keyboard_layout->addWidget(control_widget);

    auto touchpad_widget = new QWidget(this);
    touchpad_widget->setFixedHeight(500);
    auto touchpad_layout = new QHBoxLayout();
    touchpad_layout->setMargin(0);
    touchpad_layout->setSpacing(0);
    touchpad_widget->setLayout(touchpad_layout);
    auto touchpad = new Touchpad();
    touchpad_layout->addWidget(touchpad);
    auto scroll_area = new QWidget(this);
    scroll_area->setFixedWidth(150);
    auto scroll_layout = new QVBoxLayout();
    scroll_area->setLayout(scroll_layout);
    auto scrollbar = new Scrollbar();
    scroll_layout->addWidget(scrollbar);
    touchpad_layout->addWidget(scroll_area);
    connect(touchpad, &Touchpad::mouseMoved, [this](int x, int y){
       this->sendData((QString("move ") + QString::number(x) + QString(" ") + QString::number(y)).toUtf8());
    });
    connect(scrollbar, &Scrollbar::mouseMoved, [this](int x, int y){
       this->sendData((QString("scroll ") + QString::number(y)).toUtf8());
    });


    auto buttons_widget = new QWidget(this);
    buttons_widget->setFixedHeight(150);
    auto buttons_layout = new QHBoxLayout();
    buttons_widget->setLayout(buttons_layout);
    buttons_layout->addWidget(createPushButton("", [this](){
        this->sendData(CLICK_LPM.toUtf8());
    }));
    buttons_layout->addWidget(createPushButton("", [this](){
        this->sendData(CLICK_PPM.toUtf8());
    }));

    main_layout->addWidget(touchpad_widget);
    main_layout->setAlignment(touchpad_widget, Qt::AlignBottom);
    main_layout->addWidget(buttons_widget);
    main_layout->setAlignment(buttons_widget, Qt::AlignBottom);
}

QPushButton *RemoteMouseScreen::createKeyboardButton(const QString& key, const QString& msg)
{
    auto button = new QPushButton(key);
    connect(button, &QPushButton::clicked, this, [this, msg](){
       emit sendData((QString("keyboard ") + msg).toUtf8());
    });
    return button;
}
