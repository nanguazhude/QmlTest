#pragma once
#include <QtWidgets/qwidget.h>

class TestWidget : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int testValue READ getValue WRITE setValue NOTIFY valueChanged)
public:
    TestWidget(QWidget * /**/ = nullptr);

    enum Priority { 
        High =    (1 << 0), 
        Low  =    (1 << 1),
        VeryHigh= (1 << 2),
        VeryLow = (1 << 3),
    };
    //Q_ENUM(Priority)
    Q_DECLARE_FLAGS(Prioritys, Priority)
    Q_FLAGS(Prioritys)

public:
    Q_SLOT int testAdd(int ,int );
public:
    void testEnum(const Prioritys &);
public:
    int getValue() const { return $m$Value; }
    void setValue(const int & arg) { 
        if (arg == $m$Value) { return; }  
        $m$Value = arg; valueChanged();
    }
    Q_SIGNAL void valueChanged();
private:
    int $m$Value = 0;
    using Super = QWidget;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TestWidget::Prioritys)












