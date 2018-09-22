QT += quick
QT += qml
QT += core
QT += gui
QT += widgets

TARGET =   test_meta_system
TEMPLATE = app

win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
    QMAKE_CXXFLAGS += /await
}else{
    CONFIG+=c++17
}#

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../bin/debug
    CONFIG += console
}else{
    DESTDIR = $$PWD/../bin/release
    CONFIG += console
    DEFINES += NDEBUG
}

SOURCES += main.cpp \
    TestWidet.cpp

HEADERS += \
    TestWidet.hpp

