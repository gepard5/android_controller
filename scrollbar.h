#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>


class Scrollbar : public QFrame
{
    Q_OBJECT

signals:
    void mouseMoved(int ,int);

public:
    Scrollbar(QWidget * parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        starting_point = geometry().topLeft();
        dragStart = event->pos();
        current_x = event->pos().x();
        current_y = event->pos().y();
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        int y = event->pos().y() - current_y;
        if(abs(y) >= MOVE_THRESHOLD) {
            current_y = event->pos().y();
            std::cout<<"Moved"<<std::endl;
            emit mouseMoved(0, y/5);
        }
   //     setGeometry(QRect(geometry().topLeft() + event->pos() - dragStart, rect().size()));
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
     //   setGeometry(QRect(starting_point, rect().size()));
    }

private:
    QPoint dragStart;
    QPoint starting_point;
    int current_x;
    int current_y;
    const int MOVE_THRESHOLD = 80;
    const int X_THRESHOLD = 400;
    const int Y_THRESHOLD = 400;

};

#endif // SCROLLBAR_H
