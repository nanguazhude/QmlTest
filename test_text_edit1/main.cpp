#include <QtGui>
#include <QtQml>
#include <QtCore>
#include <QtQuick>
#include <QtWidgets>
#include "MyTextEdit.hpp"

int main(int argc, char ** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QDir::setCurrent(app.applicationDirPath());

    qmlRegisterType<MyTextEdit>("myqml.test_text_edit",1,0,"MyTextEdit");

    QQmlApplicationEngine engine;
    engine.load(QDir(app.applicationDirPath()).
        absoluteFilePath(QStringLiteral("myqml/test_text_edit1/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        qDebug() << "can not load:"
            << QDir(app.applicationDirPath()).absoluteFilePath(QStringLiteral("myqml/test_text_edit/main.qml"));
        return -1;
    }

    QObject * varTextEditObject = nullptr ;
    const auto & varRootObjects = engine.rootObjects();
    for (const auto & varI : varRootObjects) {
        varTextEditObject = varI->findChild<QObject *>(QStringLiteral("_id_text_edit"));
        if (varTextEditObject) { break; }
    }

    auto varEdit = dynamic_cast<MyTextEdit*>(varTextEditObject);
    if (varEdit == nullptr) { return -2; }

    for (int i = 0; i < 100 ; ++i) {

        MyTextEdit::TextFrameFormat varFormat;
        auto varFrame = varEdit->create_frame(varFormat);
        QTextCursor varFC{ varFrame };
         
        { 
            auto varBCF = varFC.blockCharFormat();
            auto varFont = varBCF.font();
            varFont.setPointSizeF(12);
            varBCF.setFont(varFont);
            varFC.setBlockCharFormat(varBCF);
        }

        varFC.insertText(QString::fromUtf8("xxxxfds ladfgsdgfd sgfdsgfdsgf dsgfdsgfd sgfdsgf dsgfdsgfd sgfdsgfdsgjf ldsjalfhd slahfldsahj fkljdsah fewoiuaf"));
        varFC.insertText("\n");
        varFC.insertText("fdasfaewwafe");
        
    }  

    return app.exec();
}

/**************************************************/

/**************************************************/
