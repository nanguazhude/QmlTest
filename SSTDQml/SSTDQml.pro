TEMPLATE = lib
TARGET = $$qtLibraryTarget(sstdqml)
QT += qml quick
CONFIG += plugin

win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
    QMAKE_CXXFLAGS += /await
}else{
    CONFIG+=c++17
}#

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

