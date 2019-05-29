#ifndef REMOTEMOUSESCREEN_H
#define REMOTEMOUSESCREEN_H

#include "screen.h"
#include <QGridLayout>

class RemoteMouseScreen : public Screen
{
public:
    RemoteMouseScreen(QWidget * parent);

protected:
    QPushButton *createKeyboardButton(const QString& key, const QString& msg = "");
    QVBoxLayout *mouse_layout;
    QLabel* mouse_label;

    const QString CLICK_LPM = "click lpm";
    const QString CLICK_PPM = "click ppm";
};

#endif // REMOTEMOUSESCREEN_H
