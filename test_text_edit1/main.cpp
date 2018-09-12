#include <QtGui>
#include <QtQml>
#include <QtCore>
#include <QtQuick>
#include <QtWidgets>
#include "MyTextEdit.hpp"
#include "GifImageProvider.hpp"

inline void setDefaultFormat() {
    auto varFormat = QSurfaceFormat::defaultFormat();
    if (varFormat.majorVersion() < 4) {
        varFormat.setVersion(4, 5);
    }
    if ((varFormat.majorVersion() == 4) && (varFormat.minorVersion() < 5)) {
        varFormat.setVersion(4, 5);
    }
    varFormat.setProfile(QSurfaceFormat::CoreProfile);
    varFormat.setSamples(3);
    varFormat.setAlphaBufferSize(8);
    varFormat.setBlueBufferSize(8);
    varFormat.setRedBufferSize(8);
    varFormat.setGreenBufferSize(8);
    varFormat.setDepthBufferSize(24);
    varFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    varFormat.setSwapInterval(0);
#if defined(ENABLE_GL_DEBUG)
    varFormat.setOption(QSurfaceFormat::DebugContext, true);
#else
    varFormat.setOption(QSurfaceFormat::DebugContext, false);
#endif
    QSurfaceFormat::setDefaultFormat(varFormat);
}

int main(int argc, char ** argv) {

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    setDefaultFormat();

    QGuiApplication app(argc, argv);
    
#if defined(QT_NO_DEBUG)
    QDir::setCurrent(app.applicationDirPath());
#else
    //QDir::setCurrent(CURRENT_DEBUG_PATH);
    QDir::setCurrent(app.applicationDirPath());
#endif

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
)");
            varFC.insertBlock();
            varFC.insertHtml(u8R"(
<p>xxfff fffffff ffffff fffffffffff ffffffffff fffffffffffff ffffffffff ffffxe 323 111 11 11111 111 11 111 1111<img src="image://GifImage/myqml/test_text_edit1/cat.gif" height="214" width="250" /></p>
)");
        }

    }  

    

    return app.exec();
}

/**************************************************/

/**************************************************/
