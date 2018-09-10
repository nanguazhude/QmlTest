#include <QtGui>
#include <QtQml>
#include <QtCore>
#include <QtQuick>
#include <QtWidgets>
#include "MyTextEdit.hpp"
#include "GifImageProvider.hpp"

int main(int argc, char ** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QDir::setCurrent(app.applicationDirPath());

    qmlRegisterType<MyTextEdit>("myqml.test_text_edit",1,0,"MyTextEdit");

    QQmlApplicationEngine engine;
    engine.load(QDir(app.applicationDirPath()).
        absoluteFilePath(QStringLiteral("myqml/test_text_edit1/main.qml")));

    engine.addImageProvider("GifImage",new GifImageProvider );

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

    

    for (int i = 0; i < 100  ; ++i) {

        MyTextEdit::TextFrameFormat varFormat;

        varFormat.setMargin(10);
        varFormat.setPadding(30);

        auto varFrame = varEdit->create_frame(varFormat);
                 
              
        {
            QTextCursor varFC{ varFrame };
            varFC.insertHtml(u8R"(
<p><font size="7" color="red">This is some text!This is some text!This is some text!This is some text!</font></p>
<p>xxfff fffffff ffffff fffffffffff ffffffffff fffffffffffff ffffffffff ffffxe 323 111 11 11111 111 11 111 1111<img src="image://GifImage/myqml/test_text_edit1/cat.gif" height="214" width="250" /></p>
)");
        }

    }  

    

    return app.exec();
}

/**************************************************/

/**************************************************/
