#ifndef VIEW_HPPxxx
#define VIEW_HPPxxx

#include <QtQuick/qquickview.h>

class View : public QQuickView {
    Q_OBJECT
public:
    View();
public:
	Q_INVOKABLE QString qmlappdir() const;
	Q_INVOKABLE double getPointRate() const;
protected:
    virtual void keyPressEvent(QKeyEvent *ev) override;
    using Super = QQuickView;
};

#endif // VIEW_HPP
