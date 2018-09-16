#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include "Window.hpp"
#include "GlobalRootItem.hpp"

Window::Window(QWindow *parent ):Super(parent){
    this->setResizeMode( Super::SizeRootObjectToView );
    this->setSource( GlobalRootItem::instance()->getFullFilePath(
                         QStringLiteral("myqml/main.qml")) );
    this->resize(512,512);
}




