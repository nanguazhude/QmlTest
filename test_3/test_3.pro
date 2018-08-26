QT += quick
QT += qml
QT += core
QT += gui
QT += widgets

TARGET = test_3
TEMPLATE = app

win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
    QMAKE_CXXFLAGS += /await
}else{
    CONFIG+=c++17
}#

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    View.cpp

RESOURCES +=  

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

HEADERS += \
    View.hpp

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../bin/debug
    CONFIG += console
}else{
    DESTDIR = $$PWD/../bin/release
    CONFIG += console
}

#buildinstall
QMAKE_POST_LINK += $$DESTDIR/buildinstall $$PWD "myqml"
export(QMAKE_POST_LINK)

DISTFILES += \
    myqml/test_3/main.qml \
    myqml/test_3/rect1.qml


