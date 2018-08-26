QT -= core 
QT -= gui
CONFIG += console

TARGET = buildinstall
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
}

DEFINES += FromDir=\\\"$$PWD\\\"
DEFINES += ToDir=\\\"$$DESTDIR\\\"

#QMAKE_EXTRA_COMPILERS
#QMAKE_EXTRA_TARGETS

SOURCES += \
    main.cpp

