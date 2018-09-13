#include "RequestTextItem.hpp"

namespace sstd{

RequestTextItem::RequestTextItem(QObject *arg) : Super(arg){

}

/**绘制边框**/
void RequestTextItem::drawFrameDecoration(
        QPainter *painter,
        QTextFrame *frame,
        QTextFrameData *fd,
        const QRectF &clip,
        const QRectF &rect) {

}

/*获得QTextFrameFormat*/
QTextFrameFormat RequestTextItem::getTextFrameFormat() const {
    return {};
}

/*获得内容*/
QList<QString> RequestTextItem::getHtmlData() const {
    return $m$HtmlData;
}

QString RequestTextItem::getHtmlTitle() const {
    return $m$HtmlTitle;
}

}/*namespace sstd*/

