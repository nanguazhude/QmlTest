#pragma once

#include <QtGui/qwindow.h>
#include "QuickWindow.hpp"

class RootWindow : public QWindow {
    Q_OBJECT
public:
    RootWindow();
protected:
    QuickWindow  * mmm_QuickWindow{nullptr};
    void resizeEvent(QResizeEvent *ev) override;
    void showEvent(QShowEvent *ev) override;
    void hideEvent(QHideEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;


private:
    using Super = QWindow;
};


