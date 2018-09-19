#include <QtGui>
#include <QtCore>
#include <QtWidgets>

#include <ClassA.hpp>

#include <typeinfo>
#include <typeindex>

typedef QObject * (*FunctionType)();

int main(int argc,char ** argv){

    QApplication varApp{argc,argv};

    QObject * classA = nullptr;
    std::type_index varTypeIndex = typeid(int);

    {
        QLibrary varLibrary;
        varLibrary.setLoadHints(QLibrary::ResolveAllSymbolsHint);
        varLibrary.setFileName(QDir(CURRENT_INSTALL_PATH).absoluteFilePath("test_library_0"));
        varLibrary.load();

        auto createTestObject = (FunctionType)varLibrary.resolve("createTestObject");
        if (createTestObject) {
            classA = createTestObject();
        }
        else {
            qDebug() << "can not load function";
        }
        varTypeIndex = typeid(*classA);

        qDebug() << varTypeIndex.name();

        delete classA;
        varLibrary.unload();

        /*type_index do not support dynamimc library*/
        //qDebug() << varTypeIndex.name();

    }

    


    QWidget varWidget;
    varWidget.show();

    return varApp.exec();
}











