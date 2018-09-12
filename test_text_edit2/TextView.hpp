#pragma once

#include <QtWidgets/qtextbrowser.h>
class QTextFrameData;

namespace sstd {

    class TextItem : public QObject {
        Q_OBJECT
    public:
        TextItem(QObject * /**/ = nullptr);

        static TextItem * getTextItem(QObject *);
        static void setTextItem(QObject *, TextItem *);

        /**绘制边框**/
        virtual void drawFrameDecoration(QPainter *painter, QTextFrame *frame, QTextFrameData *fd, const QRectF &clip, const QRectF &rect);
        /*获得QTextFrameFormat*/
        virtual QTextFrameFormat getTextFrameFormat() const = 0;
        /*获得内容*/
        virtual QList<QString> getHtmlData() const = 0;

    private:
        using Super = QObject;
    };

    class TextBrowser : public QTextBrowser {
        Q_OBJECT
    public:
        TextBrowser(QWidget *parent = nullptr);
        QTextFrame * appendTextFrame(TextItem*);
    private:
        using Super = QTextBrowser;

    };

}/*namespace sstd*/













