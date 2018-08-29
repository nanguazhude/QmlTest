TEMPLATE = lib
TARGET = $$qtLibraryTarget(sstdqml)
QT += qml quick
CONFIG += plugin

CONFIG += c++11

uri = SSTDQml
DISTFILES += $$PWD/SSTDQml/qmldir \
    SSTDQml/TestAny.qml
DISTFILES += $$PWD/SSTDQml/plugin.qmltypes

HEADERS += \
    MyRectangle.hpp \
    sstdqml_plugin.hpp

SOURCES += \
    MyRectangle.cpp \
    sstdqml_plugin.cpp

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../bin/debug/SSTDQml
    CONFIG += console
}else{
    DESTDIR = $$PWD/../bin/release/SSTDQml
    CONFIG += console
}

#buildinstall
QMAKE_POST_LINK += $$DESTDIR/../buildinstall $$PWD "SSTDQml"
export(QMAKE_POST_LINK)

