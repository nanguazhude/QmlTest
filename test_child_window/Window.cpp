#include "Window.hpp"
#include "QuickWindow.hpp"
#include <QtCore/qdebug.h>

RootWindow::RootWindow() : Super() {
    this->setMinimumSize({128,128});
    mmm_QuickWindow = new QuickWindow{this};
    this->resize(512,512);
}

void RootWindow::resizeEvent(QResizeEvent *ev) {
    if (mmm_QuickWindow) {
        const auto varSize = ev->size();
        mmm_QuickWindow->setGeometry(0,0,varSize.width(),varSize.height());
    }
    return Super::resizeEvent(ev);
}


void RootWindow::showEvent(QShowEvent *ev) {
    if (mmm_QuickWindow) {
        mmm_QuickWindow->show();
    }
    return Super::showEvent(ev);
}

void RootWindow::hideEvent(QHideEvent *ev) {
    if (mmm_QuickWindow) {
        mmm_QuickWindow->hide();
    }
    return Super::hideEvent(ev);
}

void RootWindow::mouseMoveEvent(QMouseEvent *ev){
    qDebug() << __func__;
    return Super::mouseMoveEvent(ev);
}

void RootWindow::mousePressEvent(QMouseEvent *ev){
    qDebug() << __func__;
    return Super::mousePressEvent(ev);
}

void RootWindow::mouseReleaseEvent(QMouseEvent *ev){
    qDebug() << __func__;
    return Super::mouseReleaseEvent(ev);
}










