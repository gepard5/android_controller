#ifndef REMOTEMOUSESCREEN_H
#define REMOTEMOUSESCREEN_H

#include "screen.h"
#include <QGridLayout>

class RemoteMouseScreen : public Screen
{
public:
    RemoteMouseScreen(QWidget * parent);

protected:
    /*void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;*/
    QVBoxLayout *mouse_layout;
    QLabel* mouse_label;

    const QString MOVE_UP = "move 0 -10";
    const QString MOVE_DOWN = "move 0 10";
    const QString MOVE_LEFT = "move -10 0";
    const QString MOVE_RIGHT = "move 10 0";
    const QString MOVE_UP_FAST = "move 0 -50";
    const QString MOVE_DOWN_FAST = "move 0 50";
    const QString MOVE_LEFT_FAST = "move -50 0";
    const QString MOVE_RIGHT_FAST = "move 50 0";
    const QString SCROLL_UP = "scroll 100";
    const QString SCROLL_UP_FAST = "scroll 500";
    const QString SCROLL_DOWN_FAST = "scroll -500";
    const QString SCROLL_DOWN = "scroll -100";
    const QString CLICK_LPM = "click lpm";
    const QString CLICK_PPM = "click ppm";
};

#endif // REMOTEMOUSESCREEN_H
