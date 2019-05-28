#include "selectscreen.h"

#include <QMessageBox>

SelectScreen::SelectScreen(QWidget *parent) : Screen(parent)
{
    locations = new QListWidget(this);
    main_layout->addWidget(locations);

    Location l;
    l.host = "127.0.0.1";
    l.password = "123";
    l.port = 9999;
    locations_map["a"] = l;
    l.host = "192.168.1.1";
    l.password = "125";
    locations_map["b"] = l;
    l.password = "111";
    locations_map["c"] = l;

    for( const auto& l : locations_map)
    {
        new QListWidgetItem(l.first, locations);
    }

    auto add_button = createPushButton("Add", [](){});
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
        this->changedPort(l.port);
        this->changedHost(l.host);
        this->changedPassword(l.password);
        this->showOverlappedScreen();
    });
    main_layout->addWidget(choose_button);

    auto back_button = createPushButton("Cancel", [this](){
       emit showOverlappedScreen();
    });
    main_layout->addWidget(back_button);
}


