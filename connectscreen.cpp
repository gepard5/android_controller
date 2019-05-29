#include "connectscreen.h"

#include <QTextEdit>
#include <QLabel>
#include <QIntValidator>

#include "selectscreen.h"


ConnectScreen::ConnectScreen(ServerConnection *conn, QWidget *parent) : Screen(parent, false), connection(conn)
{
    auto edit_widget = new QWidget(this);
    edit_widget->setMaximumHeight(500);
    edit_widget->setMaximumWidth(500);
    host_edit = new QLineEdit("10.1.2.169");
    auto edit_layout = new QVBoxLayout();
    edit_widget->setLayout(edit_layout);
    addToBottom(edit_widget);
    main_layout->setAlignment(edit_widget, Qt::AlignBottom);

    auto host_label = new QLabel("Host:");
    edit_layout->addWidget(host_label);
    edit_layout->addWidget(host_edit);
    password_edit = new QLineEdit("123");
    password_edit->setEchoMode(QLineEdit::Password);
    auto password_label = new QLabel("Password:");
    edit_layout->addWidget(password_label);
    edit_layout->addWidget(password_edit);

    port_edit = new QLineEdit("9999");
    port_edit->setValidator(new QIntValidator(0, 65536, this));
    auto port_label = new QLabel("Port:");
    edit_layout->addWidget(port_label);
    edit_layout->addWidget(port_edit);

    auto buttons_widget = new QWidget(this);
    auto buttons_layout = new QVBoxLayout();
    buttons_widget->setMaximumHeight(300);
    buttons_widget->setLayout(buttons_layout);
    addToBottom(buttons_widget);

    connect_button = createPushButton("Connect", [this](){ this->connectTcp(); });
    buttons_layout->addWidget(connect_button);

    auto select_button = createPushButton("Select location", [this]() {
       auto select_screen = new SelectScreen(this);
       connect(select_screen, &SelectScreen::changedHost, [this](QString h){ host_edit->setText(h); });
       connect(select_screen, &SelectScreen::changedPort, [this](QString p){ port_edit->setText(p); });
       connect(select_screen, &SelectScreen::changedPassword, [this](QString p){ password_edit->setText(p); });
       emit pushOverlappingScreen(select_screen);
    });
    buttons_layout->addWidget(select_button);

    auto back_button = createPushButton("Back to menu", [this](){ emit backToMenu(); });
    buttons_layout->addWidget(back_button);

    connect(connection, &ServerConnection::connected, this, [this](){
       this->backToMenu();
    });
}

bool ConnectScreen::connectTcp()
{
    connection->setHost(host_edit->text());
    connection->setPassword(password_edit->text());
    connection->setPort(port_edit->text().toUShort());
    connection->connectToHost();
    return connection->isConnected();
}
