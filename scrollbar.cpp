#include "scrollbar.h"

Scrollbar::Scrollbar(QWidget * parent) : QFrame(parent)
{
    QFrame::setFrameShape(QFrame::Box);
    QFrame::setLineWidth(10);
    setStyleSheet("QFrame { border-image: url(:/images/scroll.png) 0 0 0 0 stretch stretch3; }");
}
