#include "View.hpp"
#include <QtGui/qimage.h>
#include <QtGui/qguiapplication.h>
#include <QtCore/qdir.h>
#include <QtQuick/qquickitem.h>
#include <QtQml/qqmlcontext.h>
#include <QtGui/qimagereader.h>
#include <utility>
#include <type_traits>
#include <ctime>
#include <cstdlib>

class View::ViewPrivate{
    const QString $m$empty_string;
public:
    int $m$ImageHeight=0;
    int $m$ImageWidth=0;
    QString $m$ImagePath;
    int $m$ImageCount = 200;

    void clear(){
        $m$ImageHeight = 10 ;
        $m$ImageWidth =  10 ;
        $m$ImagePath = $m$empty_string;
    }

    void loadImage(){
        QDir varDir{ qApp->applicationDirPath() };
        const auto varImageDir = varDir.absoluteFilePath( QStringLiteral("shaped.png") );
        {
            bool varTryAgain = false;
            do{

                QImageReader varReader{ varImageDir };
                if( false == varReader.canRead() ){
                    if(varTryAgain){
                        this->clear();
                        return;
                    }

                    QImage varImage{ ":/_shaped.png" };
                    varImage.save(varImageDir);

                    varTryAgain = true;
                    continue;
                }

                const auto varImageSize = varReader.size();
                $m$ImageHeight =varImageSize.height();
                $m$ImageWidth = varImageSize.width();

                {
                    ++$m$ImageCount;
                    if($m$ImageCount>263){$m$ImageCount=200;}
					varDir.mkpath( varDir.absoluteFilePath("tmp") );
                    const auto varImagePath = varDir.absoluteFilePath(
                                QStringLiteral("tmp/shaped")+
                                QString::number($m$ImageCount)+
                                QStringLiteral(".png")
                                );
                    QFile::remove( varImagePath );
                    QFile::copy( varImageDir , varImagePath );
                    $m$ImagePath = varImagePath;
                }

            }while(varTryAgain);
        }
    }
};

View::View() {
    thisp = new ViewPrivate;
    thisp->loadImage();

    this->setMinimumHeight(10);
    this->setMinimumWidth(10);
    this->setResizeMode(QQuickView::SizeViewToRootObject);
    this->rootContext()->setContextProperty(QStringLiteral("myapp"), this);
    this->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
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
            thisp->loadImage();
            QMetaObject::invokeMethod(varRootObject, "image_changed", Qt::DirectConnection);
        }
        return;
    }
    return Super::keyPressEvent(e);
}

View::~View(){
    delete thisp;
}

QString View::getImagePath() const{
#ifdef Q_OS_WIN
    return QChar('/') + thisp->$m$ImagePath;
#else
    return thisp->$m$ImagePath;
#endif
}

int View::getImageWidth() const{
    return thisp->$m$ImageWidth;
}

int View::getImageHeight() const{
    return thisp->$m$ImageHeight;
}

