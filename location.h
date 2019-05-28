#ifndef LOCATION_H
#define LOCATION_H

#include <QString>

struct Location
{
public:
    Location();

    int port;
    QString password;
    QString host;
};

#endif // LOCATION_H
