#include "ReplyTextItem.hpp"
#include <QtGui>
#include <QtCore>

namespace sstd {

    ReplyTextItem::ReplyTextItem(QObject * arg) :Super(arg) {

    }

    inline double getMaxWidth(const QTextBlock & varBlock) {
        double varWith = 0;
        do {
            if (varBlock.isValid() == false) { break; }
            if (varBlock.lineCount() < 1) { break; }
            const auto varLayout = varBlock.layout();
            if (varLayout == nullptr) { break; }
            const auto varLineCout = varLayout->lineCount();
            for (int i = 0; i < varLineCout; ++i) {
                const auto varLine = varLayout->lineAt(i);
                if (varLine.isValid() == false) { continue; }
                varWith = std::max(varWith, varLine.naturalTextWidth());
            }
        } while (false);
        return varWith;
    }

    inline double getMaxWidth(QTextFrame * frame) {
        double varWith = 0;
        auto varPos = frame->begin();
        const auto varE = frame->end();
        for (; varPos != varE; ++varPos) {
            varWith = std::max(varWith, getMaxWidth(varPos.currentBlock()));
        }
        return varWith;
    }

    static inline QPainterPath make_painter_path(float x, float y, float w, float h) {

        float r = 15.0f;
        QPainterPath varAns;
        w = std::max(w, 12.0f);
        h = std::max(h, 12.0f);

        varAns.addRoundedRect(QRectF{ x,y,w,h }, r, r);
        varAns.moveTo(x+w, y + r);
        varAns.lineTo(x+w + 10, y + r + 7.5);
        varAns.lineTo(x+w, y + r + 15);
        varAns.closeSubpath();

        return varAns.simplified();
    }

    /**绘制边框**/
    void ReplyTextItem::drawFrameDecoration(
        QPainter *painter,
        QTextFrame *frame,
        QTextFrameData *fd,
        const QRectF &clip,
        const QRectF &rect) {

        painter->setRenderHint(QPainter::TextAntialiasing, true);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter->setRenderHint(QPainter::HighQualityAntialiasing, true);

        const auto varFormat = frame->frameFormat();

        float varWidth = static_cast<float>(getMaxWidth(frame) + varFormat.padding() + varFormat.padding());
        float varHeight = static_cast<float>(rect.height());
        float varX = static_cast<float>(rect.right()-varWidth-varFormat.rightMargin());
        float varY = static_cast<float>(rect.y());

        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(200,200,200,255));
        painter->drawPath(make_painter_path(varX, varY, varWidth, varHeight));

        painter->setBrush(QColor(255, 200, 200, 255));
        painter->drawRect(rect.right()-62, varY, 60, 60);

        (void)fd;
        (void)clip;
    }

    /*获得QTextFrameFormat*/
    QTextFrameFormat ReplyTextItem::getTextFrameFormat() const {
        constexpr const static unsigned char varMargin = 8;
        QTextFrameFormat varAns;
        varAns.setLeftMargin(varMargin + 32);
        varAns.setRightMargin(70 + varMargin);
        varAns.setTopMargin(varMargin);
        varAns.setBottomMargin(varMargin);
        varAns.setPadding(8);
        return { varAns };
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







