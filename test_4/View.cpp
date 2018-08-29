#include "View.hpp"
#include <QtGui/qimage.h>
#include <QtGui/qguiapplication.h>
#include <QtCore/qdir.h>
#include <QtQuick/qquickitem.h>
#include <QtQml/qqmlcontext.h>
#include <QtGui/qimagereader.h>
#include <utility>
#include <type_traits>
#include <ctime>
#include <cstdlib>

View::View(QWindow *parent) :QQuickView(parent)  {
    this->setMinimumHeight(480);
    this->setMinimumWidth(480);
    this->setResizeMode(QQuickView::SizeViewToRootObject);
    this->rootContext()->setContextProperty(QStringLiteral("myapp"), this);
    this->setSource(QUrl(QStringLiteral("myqml/test_4/main.qml")));
}

View::~View() {}

void View::keyPressEvent(QKeyEvent *ev) {
    return Super::keyPressEvent(ev);
}




