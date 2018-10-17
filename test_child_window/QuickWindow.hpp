#pragma once

#include <QtQuick/qquickview.h>

class QuickWindow : public QQuickView {
    Q_OBJECT
public:
    QuickWindow(QWindow * p);

protected:
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

private:
    using Super = QQuickView ;
};






















