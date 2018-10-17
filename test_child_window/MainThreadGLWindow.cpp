#include "MainThreadGLWindow.hpp"
#include <QtCore/qcoreapplication.h>
#include <QtGui/qopenglcontext.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/qevent.h>

MainThreadGLWindow::MainThreadGLWindow(){
    this->setSurfaceType(QSurface::OpenGLSurface);
    this->setMinimumSize({ 128,128 });
}

MainThreadGLWindow::~MainThreadGLWindow(){
    if(mmm_Contex){
        delete mmm_Contex;
    }
}

void MainThreadGLWindow::update(){
    this->init_and_repaint();
}

bool MainThreadGLWindow::event(QEvent *event)   {
    switch (event->type()) {
           case QEvent::UpdateRequest:
               this->init_and_repaint();
               return true;
           default:
               return QWindow::event(event);
       }
}

void MainThreadGLWindow::exposeEvent(QExposeEvent *event)   {
    this->init_and_repaint();
    return;
    (void)event;
}

void MainThreadGLWindow::init_and_repaint(){
    if(mmm_Contex==nullptr){
        mmm_Contex = new QOpenGLContext;
        mmm_Contex->create();
    }
    mmm_Contex->makeCurrent(this);
    auto g = mmm_Contex->functions();
    g->glViewport(0,0,this->width()*this->devicePixelRatio(),this->height()*this->devicePixelRatio());
    g->glClearColor( mmm_CleanColor[0],
            mmm_CleanColor[1],
            mmm_CleanColor[2],
            mmm_CleanColor[3] );
    g->glClear(GL_COLOR_BUFFER_BIT);
    g->glFinish();
    mmm_Contex->swapBuffers(this);
    return;
}

void MainThreadGLWindow::resizeEvent(QResizeEvent *ev) {
    if (mmm_Content) {
        const auto & varSize = ev->size();
        mmm_Content->setGeometry(0,0, varSize.width(), varSize.height());
    }
    return Super::resizeEvent(ev);
}

void MainThreadGLWindow::showEvent(QShowEvent *ev) {
    if (mmm_Content) {
        mmm_Content->show();
    }
    return Super::showEvent(ev);
}

void MainThreadGLWindow::hideEvent(QHideEvent *ev) {
    if (mmm_Content) {
        mmm_Content->hide();
    }
    return Super::hideEvent(ev);
}

void MainThreadGLWindow::setContent(QWindow *arg) {
    mmm_Content = arg;
}

