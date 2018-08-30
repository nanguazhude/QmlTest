#include <QtGui>
#include <QtQml>
#include <QtCore>
#include <QtQuick>
#include <QtWidgets>

int main(int argc, char ** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QDir::setCurrent(app.applicationDirPath());

    QQmlApplicationEngine engine;
    engine.load(QDir(app.applicationDirPath()).
        absoluteFilePath(QStringLiteral("myqml/test_text_edit/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        qDebug() << "can not load:"
            << QDir(app.applicationDirPath()).absoluteFilePath(QStringLiteral("myqml/test_text_edit/main.qml"));
        return -1;
    }

    /******************/
    QObject * varTextEditObject = nullptr;
    const auto & varRootObjects = engine.rootObjects();
    for (const auto & varI : varRootObjects) {
        varTextEditObject = varI->findChild<QObject *>(QStringLiteral("_id_text_edit"));
        if (varTextEditObject) { break; }
    }

    qDebug() << "cpp:" << varTextEditObject;
    auto varQQuickTextDocument = varTextEditObject->property("textDocument").value<QQuickTextDocument*>();
    if (varQQuickTextDocument) {

        QTextDocument * varTextDocument = varQQuickTextDocument->textDocument();
        qDebug() << varTextDocument;

        {
            {
                QTextCursor varC{ varTextDocument };
                varC.movePosition(QTextCursor::End);
                QTextFrameFormat varFormat;

                varFormat.setMargin(10);
                varFormat.setPadding(10);
                varFormat.setBorderStyle(QTextFrameFormat::BorderStyle_DotDotDash);
                varFormat.setBorder(2);
                varFormat.setBorderBrush(QBrush(QColor(1, 200, 3)));
                varFormat.setBackground(QBrush(QColor(200, 222, 200)));

                auto varFrame = varC.insertFrame(varFormat);
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

        }

        {
            {
                QTextCursor varC{ varTextDocument };
                varC.movePosition(QTextCursor::End);
                varC.insertHtml(u8R"(<img src="image.png"/>)");
            }
        }

        {
            {
                QTextCursor varC{ varTextDocument };
                varC.movePosition(QTextCursor::End);
                varC.insertText("\n\n\n");
                varC.insertHtml(u8R"(<img src="cat.gif"/>)");
            }
        }

    }

    return app.exec();
}

/**************************************************/

/**************************************************/
