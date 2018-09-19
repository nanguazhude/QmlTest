QT += quick
QT += qml
QT += core
QT += gui
QT += widgets
QT += core_private
QT += gui_private
QT += widgets_private
QT += quick_private
QT += qml_private

TARGET =   test_library_0_app
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


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

#LIBS += -L$$DESTDIR -ltest_library_0
INCLUDEPATH += $$PWD/../test_library_0

SOURCES += main.cpp

DEFINES += CURRENT_INSTALL_PATH=\\\"$$DESTDIR\\\"

