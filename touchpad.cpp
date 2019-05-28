#include "touchpad.h"

Touchpad::Touchpad(QWidget *parent) : QFrame(parent)
{
   QFrame::setFrameShape(QFrame::Box);
   QFrame::setLineWidth(10);
}
