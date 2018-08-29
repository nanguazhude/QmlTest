#pragma once

#include <QQuickItem>
#include <QQuickPaintedItem>

class MyRectangle : public QQuickPaintedItem {

    Q_OBJECT
    Q_DISABLE_COPY(MyRectangle)

    Q_PROPERTY(int testValue READ getTestValue WRITE setTestValue NOTIFY testValueChanged)

public:
    MyRectangle(QQuickItem *parent = nullptr);
    ~MyRectangle();

    int $m$Value = 1;
    int getTestValue() const { return $m$Value; }
    void setTestValue(int arg){
        if(arg==$m$Value)return;
        $m$Value = arg;
        testValueChanged();
    }
    Q_SIGNAL void testValueChanged();
protected:
    using Super = QQuickPaintedItem;
    void paint(QPainter *painter) override;
};







