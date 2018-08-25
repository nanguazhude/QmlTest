#ifndef VIEW_HPPxxx
#define VIEW_HPPxxx

#include <QtQuick/qquickview.h>

class View : public QQuickView {
    Q_OBJECT
public:
    View();
    ~View();
public:
    Q_INVOKABLE QString getImagePath() const;
    Q_INVOKABLE int getImageWidth() const;
    Q_INVOKABLE int getImageHeight() const;
protected:
    virtual void keyPressEvent(QKeyEvent *ev) override;
    using Super = QQuickView;
private:
    class ViewPrivate;
    ViewPrivate * thisp = nullptr;
};

#endif // VIEW_HPP

