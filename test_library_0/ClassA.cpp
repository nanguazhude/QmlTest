#include "ClassA.hpp"
#include <QtCore>

ClassA::ClassA(){

}

ClassA::~ClassA(){

}

extern "C" {
    SSTD_LIBRARY_EXPORT QObject * createTestObject() {
        return new ClassA;
    }
}

namespace {
    class ClassTest {
    public:
        ClassTest() {
            qDebug() << "class test";
        }
        ~ClassTest() {
            qDebug() << "~class test";
        }
    };

    static ClassTest classTest;

}/*namespace*/


