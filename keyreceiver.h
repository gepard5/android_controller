#ifndef KEYRECEIVER_H
#define KEYRECEIVER_H

#include <QObject>

class keyReceiver : public QObject
{
    Q_OBJECT
signals:
    void keyPressed(QString);
public:
    keyReceiver();
protected:
    bool eventFilter(QObject *, QEvent *);
};

#endif // KEYRECEIVER_H
