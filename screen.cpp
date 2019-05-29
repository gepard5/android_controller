#include "screen.h"

#include <QVBoxLayout>

Screen::Screen(QWidget *parent, bool addTopButtons) : QWidget(parent)
{
    main_layout = new QVBoxLayout();

    if(addTopButtons) {
        auto top_widget = new QWidget();
        auto top_layout = new QHBoxLayout();
        auto back_button = createPushButton("Back to menu", [this]() {
            emit backToMenu();
        });
        top_layout->addWidget(back_button);
        auto mouse_button = createPushButton("Mouse", [this]() {
           emit showMouse();
        });
        top_layout->addWidget(mouse_button);
        top_widget->setLayout(top_layout);
        main_layout->addWidget(top_widget);
        main_layout->setAlignment(top_widget, Qt::AlignTop);
    }

     main_layout->addStretch(0);
    setLayout(main_layout);

    this->setStyleSheet(QString("QPushButton:enabled{ border: 10px solid white; color: white; background-color: black; }") +
                        "QPushButton:disabled{ color:rgb(183. 183, 183); border: 10px solid white; background-color: black; }" +
                        "QLabel { color: white; font-size: 40px; color:rgb(38,248,255); }" +
                        "QFrame { border: 5px solid white; }");
}

QPushButton * Screen::createPushButton(const QString& msg, action push_action, int width, int height)
{
    QPushButton *button = new QPushButton(msg);
    button->setMinimumSize(QSize(width, height));
    QFont f("Arial Black", 18, QFont::Bold );
    button->setFont(f);
    connect(button, &QPushButton::clicked, this, push_action);
    return button;
}

QPushButton* Screen::createIconButton(const QString& icon_path, action push_action, int width, int height)
{
    QPushButton *button = new QPushButton();
     QPixmap pixmap(icon_path);
    button->setMinimumSize(QSize(width, height));
    button->setIcon(pixmap);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setIconSize(pixmap.rect().size());
    connect(button, &QPushButton::clicked, this, push_action);
    return button;
}

QLabel* Screen::createIconLabel(const QString& icon_path)
{
    QLabel *label = new QLabel();
    QPixmap pixmap(icon_path);
    label->setMinimumSize(10, 30);
    label->setPixmap(pixmap);
    return label;
}

void Screen::addToBottom(QWidget *widg)
{
    main_layout->addWidget(widg);
    main_layout->setAlignment(widg, Qt::AlignBottom);
}
