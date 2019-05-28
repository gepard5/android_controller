#ifndef EDITLOCATIONSCREEN_H
#define EDITLOCATIONSCREEN_H

#include "screen.h"
#include "location.h"

#include <QLineEdit>



class EditLocationScreen : public Screen
{
    Q_OBJECT
signals:
    void addLocation(QString, QString, QString, QString);

public:
    EditLocationScreen(QWidget * parent = nullptr);

    EditLocationScreen(QWidget * parent, const QString&, const Location&);

 //   ~EditLocationScreen() = default;
protected:
    QLineEdit *name_edit;
    QLineEdit *host_edit;
    QLineEdit *password_edit;
    QLineEdit *port_edit;
};

#endif // EDITLOCATIONSCREEN_H
