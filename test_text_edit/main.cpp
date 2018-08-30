#include <QtGui>
#include <QtQml>
#include <QtCore>
#include <QtQuick>
#include <QtWidgets>

int main(int argc,char ** argv){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QDir::setCurrent(app.applicationDirPath());

    QQmlApplicationEngine engine;
    engine.load(QDir(app.applicationDirPath()).
                     absoluteFilePath(QStringLiteral("myqml/test_text_edit/main.qml")));
    if (engine.rootObjects().isEmpty()){
        qDebug()<<"can not load:"
            << QDir(app.applicationDirPath()).absoluteFilePath(QStringLiteral("myqml/test_text_edit/main.qml"));
        return -1;
    }

    /******************/
    QObject * varTextEditObject;
    const auto & varRootObjects = engine.rootObjects();
    for ( const auto & varI : varRootObjects ) {
        varTextEditObject = varI->findChild<QObject *>(QStringLiteral("_id_text_edit"));
        if (varTextEditObject) { break; }
    }

    qDebug()<<"cpp:"<< varTextEditObject;
    auto varQQuickTextDocument = varTextEditObject->property("textDocument").value<QQuickTextDocument*>();
    if (varQQuickTextDocument) {
        QTextDocument * varTextDocument = varQQuickTextDocument->textDocument();



    }
    
    return app.exec();
}

/**************************************************/

/**************************************************/
