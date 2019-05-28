#include "selectscreen.h"

#include <QMessageBox>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include "editlocationscreen.h"

SelectScreen::SelectScreen(QWidget *parent) : Screen(parent)
{
    locations = new QListWidget(this);
    main_layout->addWidget(locations);

    readLocationsFromFile();

    for( const auto& l : locations_map)
    {
        new QListWidgetItem(l.first, locations);
    }

    auto add_button = createPushButton("Add", [this](){
        auto edit_screen = new EditLocationScreen(this);
        connect(edit_screen, &EditLocationScreen::addLocation, [this](QString name, QString host, QString password, QString port){
           Location l;
           l.host = host;
           l.port = port.toUShort();
           l.password = password;
           if(locations_map.count(name) != 0) {
               auto popup = new QMessageBox(QMessageBox::Warning, "Location exists",
                    "Adding location failed. Given location already exists.");
               popup->exec();
               popup->deleteLater();
               return;
           }
           locations_map[name] = l;
           new QListWidgetItem(name, locations);
        });
        emit pushOverlappingScreen(edit_screen);
    });
    main_layout->addWidget(add_button);

    auto choose_button = createPushButton("Select", [this](){
        auto item = locations->currentItem();
        if(!item) {
            auto popup = new QMessageBox(QMessageBox::Warning, "No location selected",
                 "No location selected. Select one or cancel");
            popup->exec();
            popup->deleteLater();
            return;
        }
        const auto& l = locations_map[item->text()];
        this->changedPort(QString::number(l.port));
        this->changedHost(l.host);
        this->changedPassword(l.password);
        this->showOverlappedScreen();
    });
    main_layout->addWidget(choose_button);

    auto modify_button = createPushButton("Modify", [this](){
        auto item = locations->currentItem();
        if(!item) {
            auto popup = new QMessageBox(QMessageBox::Warning, "No location selected",
                 "No location selected. Select one or cancel");
            popup->exec();
            popup->deleteLater();
            return;
        }
        auto edit_screen = new EditLocationScreen(this, item->text(), locations_map[item->text()]);
        connect(edit_screen, &EditLocationScreen::addLocation, [this](QString name, QString host, QString password, QString port){
           Location l;
           l.host = host;
           l.port = port.toUShort();
           l.password = password;
           locations_map[name] = l;
        });
        emit pushOverlappingScreen(edit_screen);
    });
    main_layout->addWidget(modify_button);

    auto delete_button = createPushButton("Delete", [this](){
       auto item = locations->currentItem();
       if(!item) {
           auto popup = new QMessageBox(QMessageBox::Warning, "No location selected",
                "No location selected. Select one or cancel");
           popup->exec();
           popup->deleteLater();
           return;
       }
       locations_map.erase(item->text());
       locations->takeItem(locations->currentRow());
    });
    main_layout->addWidget(delete_button);

    auto back_button = createPushButton("Cancel", [this](){
       emit showOverlappedScreen();
    });
    main_layout->addWidget(back_button);
}

void SelectScreen::readLocationsFromFile()
{
    QString path = QStandardPaths::displayName(QStandardPaths::AppDataLocation);
    QFile file(path);
    if( file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            QStringList list = stream.readLine().split(" ");
            Location l;
            l.host = list[1];
            l.port = list[2].toUShort();
            l.password = list[3];
            locations_map[list[0]] = l;
        }
    }
}

void SelectScreen::writeLocationsToFile()
{
    QString path = QStandardPaths::displayName(QStandardPaths::AppDataLocation);
    QFile file(path);
    if( file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
       for( const auto& l : locations_map)
       {
            const Location& loc = l.second;
            stream << l.first << " " << loc.host << " " << loc.password << " " << loc.port << "\n";
        }
    }
}
