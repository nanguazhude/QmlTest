#include <QtQuick>

class Window : public QQuickView {
    Q_OBJECT
public:
    Window(QWindow *parent =nullptr);
private:
    using Super = QQuickView;
};






