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

	QQmlComponent * component = new QQmlComponent(
		view.engine() ,
		QDir(app.applicationDirPath()).absoluteFilePath( QStringLiteral("myqml/test_3/rect1.qml") ) ,
		&view);

	{
		auto varRun = [component, &view](QQmlComponent::Status status) {
			if (status == QQmlComponent::Status::Ready) {
				qDebug() << status;
				auto varObject = component->beginCreate(view.rootContext());
				auto varItem = dynamic_cast<QQuickItem*>(varObject);
				varItem->setParent(view.rootObject());
				varItem->setParentItem(view.rootObject());
				varItem->setPosition({ 120,20 });
				component->completeCreate();
			}
			else {
				qDebug() << status;
			}
		};
		if (component->isReady()) { varRun(QQmlComponent::Status::Ready); }
	}

	return app.exec();

}



