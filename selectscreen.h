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
    void changedPort(QString);
    void changedHost(QString);
    void changedPassword(QString);

public:
    SelectScreen(QWidget *parent);
    ~SelectScreen() { writeLocationsToFile(); }
protected:
    void readLocationsFromFile();
    void writeLocationsToFile();

    QListWidget *locations;
    std::map<QString, Location> locations_map;
};





#endif // SELECTSCREEN_H
