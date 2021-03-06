#include "editlocationscreen.h"

#include <QLineEdit>
#include <QIntValidator>

EditLocationScreen::EditLocationScreen(QWidget * parent) : Screen(parent, false)
{
    auto edit_widget = new QWidget(this);
    edit_widget->setMaximumHeight(700);
    edit_widget->setMaximumWidth(700);
    host_edit = new QLineEdit("127.0.0.1");
    auto edit_layout = new QVBoxLayout();
    edit_widget->setLayout(edit_layout);
    addToBottom(edit_widget);
    main_layout->setAlignment(edit_widget, Qt::AlignBottom);

    auto name_label = new QLabel("Name: ");
    name_edit = new QLineEdit("name");
    edit_layout->addWidget(name_label);
    edit_layout->addWidget(name_edit);
    //host_edit->setMaximumHeight(30);
    auto host_label = new QLabel("Host:");
    edit_layout->addWidget(host_label);
    edit_layout->addWidget(host_edit);
    password_edit = new QLineEdit("");
    password_edit->setEchoMode(QLineEdit::Password);
    auto password_label = new QLabel("Password:");
    edit_layout->addWidget(password_label);
    edit_layout->addWidget(password_edit);

    port_edit = new QLineEdit("9999");
    port_edit->setValidator(new QIntValidator(0, 65536, this));
    auto port_label = new QLabel("Port:");
    edit_layout->addWidget(port_label);
    edit_layout->addWidget(port_edit);

    main_layout->addWidget(edit_widget);
    main_layout->addWidget(createPushButton("Add", [=](){
        auto name = name_edit->text().replace(" ", "");
        auto host = host_edit->text();
        auto password = password_edit->text();
        auto port = port_edit->text();
        emit addLocation(name, host, password, port);
        this->showOverlappedScreen();
    }));
    main_layout->addWidget(createPushButton("Cancel", [this](){
        this->showOverlappedScreen();
    }));
}

EditLocationScreen::EditLocationScreen(QWidget * parent, const QString& name, const Location& l) : EditLocationScreen(parent)
{
    name_edit->setText(name);
    name_edit->setReadOnly(true);
    port_edit->setText(QString::number(l.port));
    host_edit->setText(l.host);
    password_edit->setText(l.password);
}
