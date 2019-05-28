#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>

class DraggableLabel : public QLabel
{
    Q_OBJECT

signals:
    void mouseMoved(int ,int);


public:
    explicit DraggableLabel(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {

    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        starting_point = geometry().topLeft();
        dragStart = event->pos();
        current_x = event->pos().x();
        current_y = event->pos().y();
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        int x = event->pos().x() - current_x;
        int y = event->pos().x() - current_y;
        if((abs(y) + abs(x)) >= MOVE_THRESHOLD) {
            current_x = x;
            current_y = y;
            emit mouseMoved(x, y);
        }
        setGeometry(QRect(geometry().topLeft() + event->pos() - dragStart, rect().size()));
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        setGeometry(QRect(starting_point, rect().size()));
    }

private:
    QPoint dragStart;
    QPoint starting_point;
    int current_x;
    int current_y;
    const int MOVE_THRESHOLD = 5;
    const int X_THRESHOLD = 400;
    const int Y_THRESHOLD = 400;
};


#endif // DRAGGABLELABEL_H
