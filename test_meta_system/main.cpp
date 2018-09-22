#include <QtCore>
#include <QtGui>
#include <QtWidgets/qapplication.h>
#include "TestWidet.hpp"

int main(int argc ,char ** argv){

    QApplication varApp{argc,argv};

    TestWidget varWidget;
    varWidget.show();

    /********************************/
    auto varMetaObject = varWidget.metaObject();
    qDebug()<< varMetaObject->className();
    {/**QMetaObject::normalizedSignature()**/
       auto varCloseFunctionIndex = varMetaObject->indexOfMethod("testAdd(int,int)");
       auto varFunction = varMetaObject->method( varCloseFunctionIndex );
       int a = 1; int b = 2; int c=0;
       varFunction.invoke(&varWidget, Qt::DirectConnection, Q_RETURN_ARG(int, c), Q_ARG(int, a), Q_ARG(int, b));
       qDebug() << c;
    }
    {//Q_DECLARE_FLAGS
     //Q_FLAG
        auto varPriorityIndex = varMetaObject->indexOfEnumerator("Prioritys");
        auto varEnumerator = varMetaObject->enumerator(varPriorityIndex);
        qDebug() << varEnumerator.key(2);
        varWidget.testEnum(TestWidget::High | TestWidget::Low);
        qDebug() << varEnumerator.valueToKeys(TestWidget::High | TestWidget::Low);
    }
    {/*The Property System*/
        auto varTestValueIndex = varMetaObject->indexOfProperty("testValue");
        auto varProperty = varMetaObject->property(varTestValueIndex);
        varProperty.write(&varWidget,13);
        qDebug()<< varProperty.read(&varWidget).toInt();
    }
    /********************************/

    return varApp.exec();
    //Q_NAMESPACE
    //Q_GADGET
}











