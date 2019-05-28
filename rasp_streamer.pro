QT += widgets
QT += network

requires(qtConfig(listview))

SOURCES   = \
            command.cpp \
            commandscreen.cpp \
            connectscreen.cpp \
            draggablelabel.cpp \
            editlocationscreen.cpp \
            keypress.cpp \
            keyreceiver.cpp \
            location.cpp \
            main.cpp \
            mainwindow.cpp \
            menuwidget.cpp \
            remotekeyboardscreen.cpp \
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
            draggablelabel.h \
            editlocationscreen.h \
            keypress.h \
            keyreceiver.h \
            location.h \
            mainwindow.h \
            menuwidget.h \
            remotekeyboardscreen.h \
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
