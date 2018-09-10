#pragma once

#include <QtQuick/qquickimageprovider.h>

class GifImageProvider  
    : public QQuickImageProvider{
public:
    GifImageProvider(  );
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)override;
private:
    using Super = QQuickImageProvider;
};






