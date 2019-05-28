#include "keyreceiver.h"

#include <iostream>
#include <QEvent>

keyReceiver::keyReceiver()
{

}

bool keyReceiver::eventFilter(QObject *obj, QEvent * event)
{
     std::cout<<"Event filter"<<std::endl;
    if( event->type() == QEvent::KeyPress) {
        emit keyPressed("A");
        return false;
    }
    return QObject::eventFilter(obj, event);
}
