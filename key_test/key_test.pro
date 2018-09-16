
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

TARGET =   key_test
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

HEADERS += \
    Window.hpp \
    Application.hpp \
    GlobalRootItem.hpp


SOURCES += \
    main.cpp \
    Window.cpp \
    Application.cpp \
    GlobalRootItem.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../bin/debug
    CONFIG += console
}else{
    DESTDIR = $$PWD/../bin/release
    CONFIG += console
    DEFINES += NDEBUG
}

#buildinstall
QMAKE_POST_LINK += $$DESTDIR/buildinstall $$PWD "myqml"
export(QMAKE_POST_LINK)

DISTFILES += \
    myqml/main.qml


DEFINES += CURRENT_DEBUG_PATH=\\\"$$PWD\\\"













