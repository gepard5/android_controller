QT += widgets
QT += network
QT += androidextras

requires(qtConfig(listview))

SOURCES   = \
            command.cpp \
            commandscreen.cpp \
            connectscreen.cpp \
            editlocationscreen.cpp \
            location.cpp \
            main.cpp \
            mainwindow.cpp \
            menuwidget.cpp \
            remotemousescreen.cpp \
            screen.cpp \
            scrollbar.cpp \
            selectscreen.cpp \
            serverconnection.cpp \
            touchpad.cpp
HEADERS   = \
            command.h \
            commandscreen.h \
            connectscreen.h \
            editlocationscreen.h \
            location.h \
            mainwindow.h \
            menuwidget.h \
            remotemousescreen.h \
            screen.h \
            scrollbar.h \
            selectscreen.h \
            serverconnection.h \
            touchpad.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/rasp_streamer
INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    android-sources/AndroidManifest.xml


ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
