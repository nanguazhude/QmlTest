#include "View.hpp"
#include <QtGui/qimage.h>
#include <QtGui/qguiapplication.h>
#include <QtCore/qdir.h>
#include <QtQuick/qquickitem.h> 
#include <QtQml/qqmlcontext.h>
#include <utility>
#include <type_traits>
#include <ctime>
#include <cstdlib>

View::View() {
	this->setMinimumHeight(480);
	this->setMinimumWidth(480);
	this->setResizeMode(QQuickView::SizeViewToRootObject);
	this->rootContext()->setContextProperty(QStringLiteral("myapp"), this);
	this->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
}

double View::getPointRate() const {
	QImage varImage{
	QDir(qApp->applicationDirPath()).absoluteFilePath(QStringLiteral("shaped.png")) };
	if (std::as_const(varImage).width() < 1) { return 1; }
	if (std::as_const(varImage).height() < 1) { return 1; }
	varImage = std::as_const(varImage).convertToFormat(QImage::Format_RGBA8888);
	const auto varImageWidth = std::as_const(varImage).width();
	const auto varImageHeigth = std::as_const(varImage).height();
	const double varAllPix = varImageWidth * varImageHeigth;
	using Int = std::remove_cv_t< std::remove_reference_t< decltype(varImageHeigth) > >;
	auto varLineStart = std::as_const(varImage).bits();
	const auto varBytesPerLine = varImage.bytesPerLine();
	Int varNotNullCount = 0;
	for (Int i = 0; i < varImageHeigth; ++i) {
		auto varJudge = varLineStart + 3;
		for (Int j = 0; j < varImageWidth; ++j) {
			if (*varJudge) { ++varNotNullCount; }
			varJudge += 4;
		}
		varLineStart += varBytesPerLine;
	}
	return varNotNullCount / (varAllPix / 12.625);
}

QString View::qmlappdir() const {
	QString varAnsOrigin = QDir(qApp->applicationDirPath()).absolutePath();
	do {/*remove last / or \*/
		if (varAnsOrigin.endsWith(QChar('/'))) { varAnsOrigin.chop(1); break; }
		if (varAnsOrigin.endsWith(QChar('\\'))) { varAnsOrigin.chop(1); break; }
	} while (false);
#ifdef Q_OS_WIN
	return QChar('/') + varAnsOrigin;
#else
	return std::move(varAnsOrigin);
#endif
}

void View::keyPressEvent(QKeyEvent*e) {
	if (e->key() == Qt::Key_S) {
		e->accept();
		{
			const QImage varImage = this->grabWindow();
			const static QDir varDir{ qApp->applicationDirPath() };
			varImage.save(varDir.absoluteFilePath(QStringLiteral("grab.png")));
		}
		return;
	}
	else if (e->key() == Qt::Key_F) {
		e->accept();
		{
			QQuickItem * varRootObject = this->rootObject();
			if (nullptr == varRootObject) { return; }
			_p_update_counter(varRootObject);
			QMetaObject::invokeMethod(varRootObject, "change_image", Qt::DirectConnection);
		}
		return;
	}
	return Super::keyPressEvent(e);
}

void View::_p_update_counter(QObject * varRootObject) {
	if ((std::rand() & 7) == 0) {
		std::srand(int(std::time(nullptr))); 
	}

	auto varCount = varRootObject->property("theCounter").toInt() + 1;
	if (varCount > 164) { varCount = 100; }
	{
		QDir varDir{ qApp->applicationDirPath() };
		varDir.mkpath(varDir.absoluteFilePath(QStringLiteral("tmp")));
		const auto varTarget = varDir.absoluteFilePath(QStringLiteral("tmp/shaped") + QString::number(varCount) + QStringLiteral(".png"));
		QFile::remove(varTarget);
		QFile::copy(varDir.absoluteFilePath(QStringLiteral("shaped.png")), varTarget);
	}
	varRootObject->setProperty("theCounter", QVariant::fromValue(varCount));
}




