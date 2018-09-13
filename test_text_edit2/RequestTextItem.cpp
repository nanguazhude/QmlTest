#include "RequestTextItem.hpp"
#include <QtGui>
#include <QtCore>

namespace sstd {

    RequestTextItem::RequestTextItem(QObject *arg) : Super(arg) {

    }

    static inline QPainterPath make_painter_path(float x, float y, float w, float h) {

        float r = 15.0f;
        QPainterPath varAns;
        w = std::max(w, 12.0f);
        h = std::max(h, 12.0f);

        varAns.addRoundedRect(QRectF{ x,y,w,h }, r, r);
        varAns.moveTo(x, y + r);
        varAns.lineTo(x - 10, y + r + 7.5);
        varAns.lineTo(x, y + r + 15);
        varAns.closeSubpath();

        return varAns.simplified();
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

    /**绘制边框**/
    void RequestTextItem::drawFrameDecoration(
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

        float varWidth = static_cast<float>(getMaxWidth(frame)+ varFormat.padding()+ varFormat.padding());
        float varHeight = static_cast<float>(rect.height());
        float varX = static_cast<float>( rect.x() + varFormat.leftMargin()  );
        float varY = static_cast<float>( rect.y() );

        painter->drawPath(make_painter_path(varX,varY,varWidth,varHeight));

        painter->drawRect( 2,varY,60,60 );


        (void)fd;
        (void)clip;
    }

    /*获得QTextFrameFormat*/
    QTextFrameFormat RequestTextItem::getTextFrameFormat() const {
        constexpr const static unsigned char varMargin = 8;
        QTextFrameFormat varAns;
        varAns.setLeftMargin(70 + varMargin);
        varAns.setRightMargin(varMargin+32);
        varAns.setTopMargin(varMargin);
        varAns.setBottomMargin(varMargin);
        varAns.setPadding(8);
        return { varAns };
    }

    /*获得内容*/
    QList<QString> RequestTextItem::getHtmlData() const {
        return $m$HtmlData;
    }

    QString RequestTextItem::getHtmlTitle() const {
        return $m$HtmlTitle;
    }

}/*namespace sstd*/

