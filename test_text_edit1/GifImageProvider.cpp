
#include "GifImageProvider.hpp"
#include <QtGui/qimagereader.h>

GifImageProvider::GifImageProvider( ) :
    Super(QQuickImageProvider::Image) {}

QImage GifImageProvider::requestImage(
    const QString &id,
    QSize *size,
    const QSize &requestedSize) {

    int varWidth = 10;
    int varHeight = 10;

    {
        QImageReader varReader{ id };
        const auto varSize = varReader.size();
        varWidth = std::max(varWidth, varSize.width());
        varHeight = std::max(varHeight, varSize.height());
    }

    varWidth = std::max(varWidth, requestedSize.width());
    varHeight = std::max(varHeight, requestedSize.height());

    if (size) { *size = { varWidth,varHeight }; }

    /*这仅仅是一个占位符，返回一个透明像素即可*/
    const QImage varImage = []() {
        QImage varImage{ 10 ,10 ,QImage::Format_RGBA8888 };
        varImage.fill(QColor(std::rand()&127, std::rand() & 127, std::rand() & 127, 100 ));
        return std::move(varImage);
    }();
    return varImage;

}





