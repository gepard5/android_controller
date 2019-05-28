#include "scrollbar.h"

Scrollbar::Scrollbar(QWidget * parent) : QFrame(parent)
{
    QFrame::setFrameShape(QFrame::Box);
    QFrame::setLineWidth(10);
}
