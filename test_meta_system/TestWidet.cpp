#include "TestWidet.hpp"
#include "Test1Private.hpp"

Test1::Test1(QObject *parent) :QObject(parent) {

}

Test2::Test2(QObject *parent) : QObject(parent) {

}

class Test3 : public QObject {
    class Test1x :public Test1 {
    public:
        void run() override {}
    } test1;
    class Test2x : public Test2 {
    public:
        void run() override {}
    } test2;
public:
    Test3(QObject * arg) :QObject(arg) {}
    void run()  {

    }
};

TestWidget::TestWidget(QWidget * parent) :Super(parent) {
    new Test3(this);
}

int TestWidget::testAdd(int a, int b) { return a + b; }


void TestWidget::testEnum(const Prioritys &) {}









