#include "QuickWindow.hpp"

QuickWindow::QuickWindow(QWindow * p) : Super(p){
    this->setColor(QColor(0,0,0,0));
    this->setResizeMode( ResizeMode::SizeRootObjectToView );
    //this->setResizeMode( ResizeMode::SizeViewToRootObject );
    this->setSource(QStringLiteral("myqml/test_child_window/main.qml"));
}


void QuickWindow::mouseMoveEvent(QMouseEvent *ev) {
    Super::mouseMoveEvent(ev);
    if (ev->isAccepted()) {
        return;
    }
}

void QuickWindow::mousePressEvent(QMouseEvent *ev) {
    Super::mousePressEvent(ev);
    if (ev->isAccepted()) {
        return;
    }
}

void QuickWindow::mouseReleaseEvent(QMouseEvent *ev) {
    Super::mouseReleaseEvent(ev);
    if (ev->isAccepted()) {
        return;
    }
}







