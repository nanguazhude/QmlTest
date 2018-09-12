#pragma once

#include <map>
#include <set>
#include <chrono>
#include <QtGui/qmovie.h>
#include <QtCore/qcache.h>
#include <QtCore/qobject.h>
#include "from_qt_qtextdocumentlayout_p.h"
class QTextFrameData;
class TextBrowser;

class TextItem : public QObject {
    Q_OBJECT
public:
    TextItem(QObject * /**/ =nullptr );

    static TextItem * getTextItem(QObject *);
    static void setTextItem(QObject *, TextItem *);

    virtual void drawFrameDecoration(QPainter *painter,
        QTextFrame *frame,
        QTextFrameData *fd,
        const QRectF &clip,
        const QRectF &rect);

private:
    using Super = QObject;
};

class GifMovie : public QMovie {
    Q_OBJECT
public:
    GifMovie(const QString &);
private:
    using Super = QMovie;
};

class TextDocumentLayout : public QTextDocumentLayout {
    Q_OBJECT
public:
    TextDocumentLayout(TextBrowser *,QTextDocument *);
private:
    using Super = QTextDocumentLayout;
    TextBrowser * const $m$TextBrowser;
protected:

    void drawInlineObject(QPainter *painter, const QRectF &rect, QTextInlineObject object, int posInDocument, const QTextFormat &format)override;
    void positionInlineObject(QTextInlineObject item, int posInDocument, const QTextFormat &format) override;
    void resizeInlineObject(QTextInlineObject item, int posInDocument, const QTextFormat &format) override;

protected:
    bool event(QEvent *) override;
    std::chrono::high_resolution_clock::time_point $m$LastGifLayoutTimeStamp;
    void relayoutGifObjects();

    class GifItemKey {
    public:
        QString name;
        friend bool operator <(const GifItemKey & l, const GifItemKey &r) { return l.name < r.name; }
        friend bool operator <(const QString & l, const GifItemKey &r) { return l < r.name; }
        friend bool operator <(const GifItemKey & l, const QString &r) { return l.name < r; }
        GifItemKey(QString && arg):name(std::move(arg)) {}
        GifItemKey(const QString & arg):name(arg) {}
        GifItemKey() = default;
        GifItemKey(const GifItemKey &)=default;
        GifItemKey(GifItemKey&&)=default;
        GifItemKey&operator=(const GifItemKey &) = default;
        GifItemKey&operator=(GifItemKey&&) = default;
    };

    class GifItemValue {
    public:
        int posInDocument = 0;
        QString name;
        friend bool operator <(const GifItemValue & l, const GifItemValue &r) { return l.posInDocument < r.posInDocument; }
        friend bool operator <(const int & l, const GifItemValue &r) { return l < r.posInDocument; }
        friend bool operator <(const GifItemValue & l, const int &r) { return l.posInDocument < r; }
        GifItemValue(int a,const QString & b) :posInDocument(a),name(b) {}
        GifItemValue(int a, QString && b) :posInDocument(a), name(std::move(b)) {}
        GifItemValue() = default;
        GifItemValue(const GifItemValue&) = default;
        GifItemValue(GifItemValue&&)=default;
        GifItemValue&operator=(const GifItemValue&) = default;
        GifItemValue&operator=(GifItemValue&&) = default;
    };
    using GifLayoutDataType = std::map<GifItemKey, std::set<GifItemValue, std::less<void>>, std::less<void>>;
    GifLayoutDataType $m$GifItemLayoutData;
    QCache<QString, GifMovie> $m$MovieCache;

    void insertMovie(const QString &);
    void updateMovie(const QString &);
};

class TextDocument : public QTextDocument {
    Q_OBJECT
public:
    TextDocument(TextBrowser *,QObject *parent );

    QTextFrame * appendTextFrame(const QTextFrameFormat &,TextItem*);

private:
    using Super = QTextDocument;
    TextBrowser * const $m$TextBrowser;
};



