#include "browserscreen.h"

#include <QVBoxLayout>
#include <QtWebView>

BrowserScreen::BrowserScreen()
{
    auto main_layout = new QVBoxLayout();
    auto browser = new QWebView(this);

}
