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
    /*获得标题*/
    QString getHtmlTitle() const override;

    template<typename Args>
    inline void setHtmlData(Args && args) { $m$HtmlData = std::forward<Args>(args); }
    template<typename Args>
    inline void setHtmlTitle(Args && args) { $m$HtmlTitle = std::forward<Args>(args); }
private:
    using Super = TextItem;
    QList<QString> $m$HtmlData;
    QString $m$HtmlTitle;
};

}/*namespace sstd*/

