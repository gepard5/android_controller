#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>

class Touchpad : public QFrame
{
    Q_OBJECT

signals:
    void mouseMoved(int ,int);

public:
    Touchpad(QWidget * parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        std::cout<<"MousePressEvent"<<std::endl;
        starting_point = geometry().topLeft();
        dragStart = event->pos();
        current_x = event->pos().x();
        current_y = event->pos().y();
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        int x = event->pos().x() - current_x;
        int y = event->pos().y() - current_y;
        std::cout<<"Mouse position: "<<x<<" "<<y<<std::endl;
        std::cout<<"Original position: "<<event->pos().x()<<" "<<event->pos().y()<<std::endl;
        std::cout<<"Current: "<<current_x<<" "<<current_y<<std::endl;
        if((abs(y) + abs(x)) >= MOVE_THRESHOLD) {
            current_x = event->pos().x();
            current_y = event->pos().y();
            std::cout<<"Moved"<<std::endl;
            emit mouseMoved(x/5, y/5);
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
    const int MOVE_THRESHOLD = 30;
    const int X_THRESHOLD = 400;
    const int Y_THRESHOLD = 400;

};

#endif // TOUCHPAD_H
