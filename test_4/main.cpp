#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtQml>
#include <QtQuick>
#include "View.hpp"

int main(int argc, char *argv[]) {

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);
	QDir::setCurrent(app.applicationDirPath());

	View view;
	view.show();

	//view.engine()->addImportPath(QStringLiteral("./myqml/test_3"));
	//qDebug() << view.engine()->importPathList();

	return app.exec();

}

/*
Dynamic QML Object Creation from JavaScript
*/




