#include "GlobalRootItem.hpp"
#include <QtCore/qdir.h>
#include <QtCore/qcoreapplication.h>

GlobalRootItem::GlobalRootItem(QObject *parent):Super(parent){

}

QString GlobalRootItem::getFullFilePath(const QString & arg) const{

#if defined(_DEBUG)
    const QDir varRootDir{ CURRENT_DEBUG_PATH };
#else
    const QDir varRootDir{ qApp->applicationDirPath() };
#endif

    const auto varAns = varRootDir.absoluteFilePath(arg);
    if( varAns.startsWith(QChar('/')) ){
        return QStringLiteral(R"(file://)")+varAns;
    }else{
        return QStringLiteral(R"(file:///)")+varAns;
    }

}

GlobalRootItem * GlobalRootItem::instance(){
    static auto * varAns = new GlobalRootItem;
    return varAns;
}




















