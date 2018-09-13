#pragma once

#include "TextView.hpp"

namespace sstd{

class RequestTextItem : public TextItem {
    Q_OBJECT
public:
    RequestTextItem(QObject * arg =nullptr);

    /**绘制边框**/
    virtual void drawFrameDecoration(QPainter *painter, QTextFrame *frame, QTextFrameData *fd, const QRectF &clip, const QRectF &rect) override;
    /*获得QTextFrameFormat*/
    virtual QTextFrameFormat getTextFrameFormat() const override ;
    /*获得内容*/
    virtual QList<QString> getHtmlData() const override;
private:
    using Super = RequestTextItem;
};

}/*namespace sstd*/

