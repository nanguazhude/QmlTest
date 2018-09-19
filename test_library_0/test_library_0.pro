TEMPLATE = lib

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES *= SSTD_LIBRARY_DLL

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

win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
    QMAKE_CXXFLAGS += /await
}else{
    CONFIG+=c++17
}#

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../bin/debug
}else{
    DESTDIR = $$PWD/../bin/release
    DEFINES += NDEBUG
}

HEADERS += test_library_0_global.hpp \
    ClassA.hpp

SOURCES += \
    ClassA.cpp

