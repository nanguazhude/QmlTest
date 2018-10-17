#include "MainThreadGLWindow.hpp"
#include <QtCore/qcoreapplication.h>
#include <QtGui/qopenglcontext.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/qevent.h>
#include <QtQuick/qquickwindow.h>
#include <QtCore/qtimer.h>
#include <QtQuick/qquickitem.h>
#include <QtCore/qrunnable.h>
#include <chrono>

using namespace std::chrono_literals;

MainThreadGLWindow::MainThreadGLWindow() {
    this->setSurfaceType(QSurface::OpenGLSurface);
    this->setMinimumSize({ 128,128 });
}

MainThreadGLWindow::~MainThreadGLWindow() {
    if (mmm_Contex) {
        delete mmm_Contex;
    }
}

void MainThreadGLWindow::update() {
    this->init_and_repaint();
}

bool MainThreadGLWindow::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::UpdateRequest:
            this->init_and_repaint();
            return true;
        default:
            return QWindow::event(event);
    }
}

void MainThreadGLWindow::exposeEvent(QExposeEvent *event) {
    this->init_and_repaint();
    return;
    (void)event;
}

void MainThreadGLWindow::init_and_repaint() {
   if (mmm_Contex == nullptr) {
       mmm_Contex = new QOpenGLContext;
       mmm_Contex->create();
   }
  mmm_Contex->makeCurrent(this);
  auto g = mmm_Contex->functions();
  g->glViewport(0, 0, this->width()*this->devicePixelRatio(), this->height()*this->devicePixelRatio());
  g->glClearColor(mmm_CleanColor[0],
      mmm_CleanColor[1],
      mmm_CleanColor[2],
      mmm_CleanColor[3]);
  g->glClear(GL_COLOR_BUFFER_BIT);
  g->glFinish();
  mmm_Contex->swapBuffers(this);
   return;
}

void MainThreadGLWindow::resizeEvent(QResizeEvent *ev) {
    if (mmm_Content) {
        const auto & varSize = ev->size();
        
       mmm_Content->setGeometry(0,0,varSize.width(),varSize.height());

         while (this->mmm_RenderState.load()!= QQuickWindow::AfterSwapStage) {
             if (this->mmm_RenderState.load() == QQuickWindow::BeforeSynchronizingStage) {
                 break;
             }
             if (this->mmm_RenderState.load() == QQuickWindow::AfterSynchronizingStage) {
                 break;
             }
         }
         qDebug() << this->mmm_RenderState.load();

    }
    this->update();
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

template<QQuickWindow::RenderStage V>
class TestData : public QRunnable {
    MainThreadGLWindow * const super;
public:
    TestData(MainThreadGLWindow * a):super(a) {
    }

    void run() {
        qDebug() << V;
        super->mmm_RenderState.store(V);
    }

    ~TestData() {
        qDebug() << "d";
    }

};

void MainThreadGLWindow::setContent(QQuickView *arg) {
    assert(mmm_Content == nullptr);
    mmm_Content = arg;

    /**
0 QQuickWindow::BeforeSynchronizingStage
1 QQuickWindow::AfterSynchronizingStage
2 QQuickWindow::BeforeRenderingStage
3 QQuickWindow::AfterRenderingStage
4 QQuickWindow::AfterSwapStage
QQuickWindow::NoStage
    **/
       
    mmm_Content->scheduleRenderJob(new TestData<QQuickWindow::BeforeSynchronizingStage>(this), QQuickWindow::BeforeSynchronizingStage);
    mmm_Content->scheduleRenderJob(new TestData<QQuickWindow::AfterSynchronizingStage>(this), QQuickWindow::AfterSynchronizingStage);
    mmm_Content->scheduleRenderJob(new TestData<QQuickWindow::BeforeRenderingStage>(this), QQuickWindow::BeforeRenderingStage);
    mmm_Content->scheduleRenderJob(new TestData<QQuickWindow::AfterRenderingStage>(this), QQuickWindow::AfterRenderingStage);
    mmm_Content->scheduleRenderJob(new TestData<QQuickWindow::AfterSwapStage>(this), QQuickWindow::AfterSwapStage);
    mmm_Content->scheduleRenderJob(new TestData<QQuickWindow::NoStage>(this), QQuickWindow::NoStage);

    using T = QQuickView;
    using I = MainThreadGLWindow;
    connect(mmm_Content, &T::beforeSynchronizing, mmm_Content, [this]() { mmm_RenderState.store(QQuickWindow::BeforeSynchronizingStage); },Qt::DirectConnection);
    connect(mmm_Content, &T::afterSynchronizing, mmm_Content, [this]() { mmm_RenderState.store(QQuickWindow::AfterSynchronizingStage); }, Qt::DirectConnection);
    connect(mmm_Content, &T::beforeRendering, mmm_Content, [this]() { mmm_RenderState.store(QQuickWindow::BeforeRenderingStage); }, Qt::DirectConnection);
    connect(mmm_Content, &T::afterRendering, mmm_Content, [this]() { mmm_RenderState.store(QQuickWindow::AfterRenderingStage); }, Qt::DirectConnection);
    connect(mmm_Content, &T::frameSwapped, mmm_Content, [this]() { mmm_RenderState.store(QQuickWindow::AfterSwapStage); }, Qt::DirectConnection);
    //connect(mmm_Content, &T::beforeSynchronizing, mmm_Content, [this]() { mmm_RenderState.store(QQuickWindow::NoStage); });




}

