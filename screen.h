#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QVBoxLayout>

#include <functional>

class Screen : public QWidget
{
    Q_OBJECT
public:
    using action = std::function<void()>;
    explicit Screen(QWidget *parent = nullptr, bool addTopButton = true);

    QPushButton* createPushButton(const QString& msg, action push_action, int width = 30, int height = 100);
    QPushButton* createIconButton(const QString& icon_path, action push_action, int width = 30, int height = 10);
    QLabel* createIconLabel(const QString& icon_path);
signals:
    void pushScreen(Screen *scr);
    void pushOverlappingScreen(Screen *scr);
    void showOverlappedScreen();
    void backToMenu();
    void sendData(QByteArray);
    void showKeyboard();
    void showMouse();

public slots:

protected:
    void addToBottom(QWidget *widg);
    QVBoxLayout *main_layout;

};

#endif // SCREEN_H
