#include "connectscreen.h"

#include <QTextEdit>
#include <QLabel>
#include <QIntValidator>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>

#include "selectscreen.h"


ConnectScreen::ConnectScreen(ServerConnection *conn, QWidget *parent) : Screen(parent, false), connection(conn)
{
    auto edit_widget = new QWidget(this);
    edit_widget->setMaximumHeight(500);
    edit_widget->setMaximumWidth(500);
    host_edit = new QLineEdit("127.0.0.1");
    auto edit_layout = new QVBoxLayout();
    edit_widget->setLayout(edit_layout);
    addToBottom(edit_widget);
    main_layout->setAlignment(edit_widget, Qt::AlignBottom);

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

    auto buttons_widget = new QWidget(this);
    auto buttons_layout = new QVBoxLayout();
    buttons_widget->setMaximumHeight(300);
    buttons_widget->setLayout(buttons_layout);
    addToBottom(buttons_widget);

    connect_button = createPushButton("Connect", [this](){ this->connectTcp(); });
    buttons_layout->addWidget(connect_button);

    readLocationsFromFile();
    setFieldsFromLocation(current_location);
    auto select_button = createPushButton("Select location", [this]() {
       auto select_screen = new SelectScreen(this, locations_map);
       connect(select_screen, &SelectScreen::locationSelected, this, [this](QString l){ current_location = l; setFieldsFromLocation(l); });
       emit pushOverlappingScreen(select_screen);
    });
    buttons_layout->addWidget(select_button);

    auto back_button = createPushButton("Back to menu", [this](){ emit backToMenu(); });
    buttons_layout->addWidget(back_button);

    connect(connection, &ServerConnection::connected, this, [this](){
       this->backToMenu();
    });
}

void ConnectScreen::setFieldsFromLocation(const QString& l)
{
    if( locations_map.count(l) != 0 ) {
        Location loc = locations_map[l];
        host_edit->setText(loc.host);
        port_edit->setText(QString::number(loc.port));
        password_edit->setText(loc.password);
    }
}

bool ConnectScreen::connectTcp()
{
    connection->setHost(host_edit->text());
    connection->setPassword(password_edit->text());
    connection->setPort(port_edit->text().toUShort());
    connect_button->setEnabled(false);
    connection->connectToHost();
    connect_button->setEnabled(true);
    return connection->isConnected();
}

void ConnectScreen::readLocationsFromFile()
{
    QString path = QStandardPaths::displayName(QStandardPaths::AppDataLocation);
    QFile file(path);
    if( file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        if(!stream.atEnd()) {
            current_location = stream.readLine().trimmed();
        }
        while(!stream.atEnd()) {
            QStringList list = stream.readLine().split(" ");
            Location l;
            l.host = list[1];
            l.port = list[3].toUShort();
            l.password = list[2];
            locations_map[list[0]] = l;
        }
    }
}

void ConnectScreen::writeLocationsToFile()
{
    QString path = QStandardPaths::displayName(QStandardPaths::AppDataLocation);
    QFile file(path);
    if( file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << current_location << "\n";
       for( const auto& l : locations_map)
       {
            const Location& loc = l.second;
            stream << l.first << " " << loc.host << " " << loc.password << " " << loc.port << "\n";
        }
    }
}

ConnectScreen::~ConnectScreen()
{
    writeLocationsToFile();
}
