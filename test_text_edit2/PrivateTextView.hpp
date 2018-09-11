#pragma once

#include <QtCore/qobject.h>
#include "from_qt_qtextdocumentlayout_p.h"
class QTextFrameData;

class TextItem : public QObject {
    Q_OBJECT
public:
    TextItem(QObject * /**/ =nullptr );

    static TextItem * getTextItem(QObject *);
    static void setTextItem(QObject *, TextItem *);

    void drawFrameDecoration(QPainter *painter,
        QTextFrame *frame,
        QTextFrameData *fd,
        const QRectF &clip,
        const QRectF &rect);

private:
    using Super = QObject;
};

class TextDocumentLayout : public QTextDocumentLayout {
    Q_OBJECT
public:
    TextDocumentLayout(QTextDocument *);
private:
    using Super = QTextDocumentLayout;
};

class TextDocument : public QTextDocument {
    Q_OBJECT
public:
    TextDocument(QObject *parent = nullptr);
private:
    using Super = QTextDocument;
};

