#include "ReplyTextItem.hpp"

namespace sstd{

ReplyTextItem::ReplyTextItem(QObject * arg):Super(arg){

}

/**绘制边框**/
void ReplyTextItem::drawFrameDecoration(
        QPainter *painter,
        QTextFrame *frame,
        QTextFrameData *fd,
        const QRectF &clip,
        const QRectF &rect) {

}

/*获得QTextFrameFormat*/
QTextFrameFormat ReplyTextItem::getTextFrameFormat() const {
    return{};
}

/*获得内容*/
QList<QString> ReplyTextItem::getHtmlData() const {
    return $m$HtmlData;
}

/*获得标题*/
QString ReplyTextItem::getHtmlTitle() const {
    return $m$HtmlTitle;
}

}/*namespace sstd*/







