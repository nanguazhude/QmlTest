#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtQml>
#include <QtQuick>
#include "View.hpp"

int main(int argc, char *argv[]) {

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);

	do {/*we force to load plugins*/
		const QImage varImage{ QStringLiteral(":/_shaped.png") };
		const QString varImageFileName = QDir(app.applicationDirPath())
			.absoluteFilePath(QStringLiteral("shaped.png"));
		{
			const QFileInfo varFileInfo(varImageFileName);
			if (varFileInfo.exists()) { break; }
		}
		varImage.save(varImageFileName);
	} while (false);

	{
		QDir varDir{ qApp->applicationDirPath() };
		varDir.mkpath(varDir.absoluteFilePath(QStringLiteral("tmp")));
		for (int varCount = 100; varCount < 103; ++varCount) {
			const auto varTarget = varDir.absoluteFilePath(QStringLiteral("tmp/shaped") + QString::number(varCount) + QStringLiteral(".png"));
			QFile::remove(varTarget);
			QFile::copy(varDir.absoluteFilePath(QStringLiteral("shaped.png")), varTarget);
		}
	}

	View view;
	view.show();

	return app.exec();
}





