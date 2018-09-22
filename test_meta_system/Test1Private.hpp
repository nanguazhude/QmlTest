#pragma once

#include <QtCore/qobject.h>

class Test1 : public QObject {
    Q_OBJECT
private:
public:
    Test1(QObject * /**/ = nullptr);
    Q_SLOT virtual void run() =0;
public:
    Q_SIGNAL void test();
    Q_SIGNAL void test1();
};

class Test2 : public QObject {
    Q_OBJECT
private:
public:
    Test2(QObject * /**/ = nullptr);
    Q_SLOT virtual void run() =0;
};

/* QObject不支持虚继承 */





