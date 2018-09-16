#pragma once

#include <QtCore/qobject.h>

class GlobalRootItem : public QObject {
    Q_OBJECT
public:
    GlobalRootItem(QObject * parent = nullptr);

    QString getFullFilePath(const QString &) const;
    static GlobalRootItem * instance();
private:
    using Super = QObject;
};

 
