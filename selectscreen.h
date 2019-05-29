#ifndef SELECTSCREEN_H
#define SELECTSCREEN_H

#include <QListWidget>

#include <map>
#include "screen.h"
#include "location.h"

class SelectScreen : public Screen
{
    Q_OBJECT
signals:
    void locationSelected(QString);

public:
    SelectScreen(QWidget *parent, std::map<QString, Location>& lm);
    ~SelectScreen() {}
protected:
    QListWidget *locations;
    std::map<QString, Location>& locations_map;
};





#endif // SELECTSCREEN_H
