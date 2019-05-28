#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <QWidget>

class KeyPress : public QWidget
{
    Q_OBJECT
signals:
    void keyPressed(QString);

public:
    KeyPress(QWidget * parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // KEYPRESS_H
