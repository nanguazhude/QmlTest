#include "ReplyTextItem.hpp"

namespace sstd{

ReplyTextItem::ReplyTextItem(QObject * arg):Super(arg){

}

/**绘制边框**/
virtual void drawFrameDecoration(
        QPainter *painter,
        QTextFrame *frame,
        QTextFrameData *fd,
        const QRectF &clip,
        const QRectF &rect) {

}

/*获得QTextFrameFormat*/
virtual QTextFrameFormat getTextFrameFormat() const {

}

/*获得内容*/
virtual QList<QString> getHtmlData() const {

}

}/*namespace sstd*/







