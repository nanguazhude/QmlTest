/**
本代码用于快速测试，不考虑异常，不考虑null指针
**/

#include <list>
#include <chrono>
using namespace std::chrono_literals;

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <vector>

#include <QtCore/qpointer.h>
#include <QtGui/qpainter.h>

#include "PrivateTextView.hpp"
#include "TextView.hpp"

namespace {

    class UpdateEvent : public QEvent {
    public:
        UpdateEvent() :Super(QEvent::User) {}
    private:
        using Super = QEvent;
    };

    class RelayoutGifEvent : public UpdateEvent {};

    /*获得可见区域对应的viewport*/
    inline QRect mapToViewport(const TextBrowser * arg) {
        auto varSize = arg->size();
        auto varVB = arg->verticalScrollBar();
        auto varHB = arg->horizontalScrollBar();
        auto varCM = arg->contentsMargins();
        varSize.setWidth(varSize.width() - varCM.left() - varCM.right());
        varSize.setHeight(varSize.height() - varCM.top() - varCM.bottom());
        return{ QPoint(varHB->value(),varVB->value()),varSize };
    }

    /*获得可见区域对应的QTextBlock*/
    inline std::vector<QTextBlock> getVisibleBlocks(const TextBrowser * arg) {

        auto varDocument = arg->document();
        auto varTextLayout = varDocument->documentLayout();
        auto varTextDocumentRect = mapToViewport(arg);
        auto varCursorPos = varTextLayout->hitTest(varTextDocumentRect.center(), Qt::FuzzyHit);
        auto varBlock = varDocument->findBlock(varCursorPos);

        if (varBlock.isValid() == false) {
            return {};
        }

        if (varTextLayout->blockBoundingRect(varBlock).
            intersects(varTextDocumentRect) == false) {
            return{};
        }

        std::list<QTextBlock> varPre;
        std::list<QTextBlock> varLast;

        varPre.push_front(varBlock.previous());
        varLast.push_front(varBlock.next());

        for (;;) {
            if (varPre.empty()) { break; }
            const auto & varBlock = varPre.front();
            if ((varBlock.isValid()) && varTextLayout->blockBoundingRect(varBlock).
                intersects(varTextDocumentRect)) {
                varPre.push_front(varBlock.previous());
                continue;
            }
            else {
                varPre.pop_front();
                break;
            }
        }

        for (;;) {
            if (varLast.empty()) { break; }
            const auto & varBlock = varLast.back();
            if ((varBlock.isValid()) && varTextLayout->blockBoundingRect(varBlock).
                intersects(varTextDocumentRect)) {
                varLast.push_back(varBlock.next());
                continue;
            }
            else {
                varLast.pop_back();
                break;
            }
        }

        std::vector<QTextBlock> varAns;
        varAns.reserve(1 + varLast.size() + varPre.size());

        varPre.push_back(varBlock);
        varPre.merge(std::move(varLast));

        varAns.assign(std::make_move_iterator(varPre.begin()),
            std::make_move_iterator(varPre.end()));

        return std::move(varAns);
    }



}/****/

TextItem::TextItem(QObject * arg) :Super(arg) {

}

TextDocumentLayout::TextDocumentLayout(TextBrowser*argB, QTextDocument *arg) :
    Super(arg),
    $m$TextBrowser(argB) {

}

TextDocument::TextDocument(TextBrowser*argB, QObject *arg) :
    Super(arg),
    $m$TextBrowser(argB) {
    this->setDocumentLayout(new TextDocumentLayout{ argB,this });
}

TextBrowser::TextBrowser(QWidget * arg) : Super(arg) {
    this->setAcceptRichText(true);
    this->setMinimumWidth(64);
    this->setMinimumHeight(64);
    auto varDocument = new TextDocument{ this, this };
    this->setDocument(varDocument);
    /***********************************************************/
#define TESTTEXTBROWSER
#if defined(TESTTEXTBROWSER)
    QTextFrameFormat varFormat;

    for (int i = 0; i < 100; ++i) {
        QTextCursor varCursor{ varDocument->appendTextFrame(varFormat, new TextItem{}) };
        for (int j = 0; j < (1 + (std::rand() & 3)); ++j) {
            varCursor.insertHtml(QStringLiteral(R"___(
<p>
    <font size="17" color="purple">today is a fine day!</font>
</p>
)___"));
        }
    }

#endif
    /***********************************************************/
}

static inline constexpr const char * propertyName() { return "\xF1" "text_item_property_name"; }

TextItem * TextItem::getTextItem(QObject * arg) {
    QVariant varAns = arg->property(propertyName());
    if (varAns.isValid() == false) { return nullptr; }
    return dynamic_cast<TextItem *>(varAns.value< QPointer< QObject > >().data());
}

void TextItem::setTextItem(QObject * arg, TextItem * var) {
    var->setParent(arg);
    arg->setProperty(propertyName(),
        QVariant::fromValue< QPointer< QObject > >(QPointer< QObject >{var}));
}

void TextItem::drawFrameDecoration(
    QPainter *painter,
    QTextFrame *frame,
    QTextFrameData *fd,
    const QRectF &clip,
    const QRectF &rect) {

    painter->setRenderHint(QPainter::TextAntialiasing, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);

    painter->setPen(QPen(QColor(255, 0, 0, 255)));
    painter->setBrush(QColor(200, 200, 189, 255));
    painter->drawRect(rect);

    (void)frame;
    (void)fd;
    (void)clip;
}

QTextFrame * TextDocument::appendTextFrame(const QTextFrameFormat & varF, TextItem * arg) {
    QTextCursor varTC{ this->rootFrame() };
    varTC.movePosition(QTextCursor::End);
    auto varAns = varTC.insertFrame(varF);
    TextItem::setTextItem(varAns, arg);
    return varAns;
}

void TextDocumentLayout::drawInlineObject(
    QPainter *painter,
    const QRectF &rect,
    QTextInlineObject object,
    int posInDocument,
    const QTextFormat &format) {
    
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);

    if (false == format.isImageFormat()) { 
        Super::drawInlineObject(painter, rect, object, posInDocument, format);
        return; 
    }

    const auto varImageCharFormat = format.toImageFormat();
    auto varImageName = varImageCharFormat.name();
    if (false == varImageName.endsWith(QStringLiteral(".gif"),
        Qt::CaseInsensitive)) {
        Super::drawInlineObject(painter, rect, object, posInDocument, format);
        return;
    }

    insertMovie(varImageName);

    auto varMovie = $m$MovieCache.object(varImageName);
    if (varMovie==nullptr) {
        Super::drawInlineObject(painter, rect, object, posInDocument, format);
        return;
    }
    else {
        const QImage varImage = varMovie->currentImage();
        painter->drawImage(rect, varImage);
        return;
    }
    
}

void TextDocumentLayout::positionInlineObject(
    QTextInlineObject item,
    int posInDocument,
    const QTextFormat &format) {
    Super::positionInlineObject(item, posInDocument, format);
    QCoreApplication::postEvent(this, new RelayoutGifEvent);
}

void TextDocumentLayout::resizeInlineObject(
    QTextInlineObject item,
    int posInDocument,
    const QTextFormat &format) {
    Super::resizeInlineObject(item, posInDocument, format);
    QCoreApplication::postEvent(this, new RelayoutGifEvent);
}

bool TextDocumentLayout::event(QEvent * e) {
    if (dynamic_cast<RelayoutGifEvent*>(e)) {
        e->accept();
        relayoutGifObjects();
        return true;
    }
    return Super::event(e);
}

void TextDocumentLayout::relayoutGifObjects() {

    {/*每隔一段时间调用此函数，避免过于频繁的调用*/
        auto varCurrentTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::abs(varCurrentTime - $m$LastGifLayoutTimeStamp) < 8ms) {
            QCoreApplication::postEvent(this, new RelayoutGifEvent);
            return;
        }
        $m$LastGifLayoutTimeStamp = varCurrentTime;
    }

    auto varVisibleBlock = getVisibleBlocks($m$TextBrowser);
    if (varVisibleBlock.empty()) {
        $m$GifItemLayoutData.clear();
        $m$MovieCache.setMaxCost(8);
        return;
    }

    GifLayoutDataType varData;
    for (const auto & varBlock : varVisibleBlock) {
        auto varCharFormatPos = varBlock.begin();
        for (; !(varCharFormatPos.atEnd()); ++varCharFormatPos) {
            auto varFragment = varCharFormatPos.fragment();
            auto varCharFormat = varFragment.charFormat();
            if (varCharFormat.isImageFormat() == false) {
                continue;
            }
            auto varImageCharFormat = varCharFormat.toImageFormat();
            auto varImageName = varImageCharFormat.name();
            if (false == varImageName.endsWith(QStringLiteral(".gif"),
                Qt::CaseInsensitive)) {
                continue;
            }
            auto varPos = varData.try_emplace(varImageName);
            const auto lp = varFragment.position() + varFragment.length();
            for (int p = varFragment.position(); p < lp; ++p) {
                varPos.first->second.emplace(p, varImageName);
            }
        }
    }

    $m$GifItemLayoutData = std::move(varData);



    $m$MovieCache.setMaxCost(static_cast<int>(8 + $m$GifItemLayoutData.size()));

}


void TextDocumentLayout::insertMovie(const QString & arg) {
    if (arg.isEmpty()) { return; }
    auto varMovie = $m$MovieCache.object(arg);
    if (varMovie) { return; }

    varMovie = new GifMovie(arg);
    varMovie->start();

    if (varMovie->isValid() == false) {
        varMovie->stop();
        varMovie->deleteLater();
        qDebug() << (QStringLiteral("can not load : ") + arg);
        return;
    }

    $m$MovieCache.insert(arg, varMovie, 1);
    connect(varMovie, &QMovie::frameChanged, 
        this, [varMovieName = arg,this](int) { updateMovie(varMovieName); });
        
}

GifMovie::GifMovie(const QString & arg) {
    this->setCacheMode(QMovie::CacheAll);
    this->setFileName( arg );
}

void TextDocumentLayout::updateMovie(const QString & arg) {
    qDebug() << "movie changed : " << arg;

}

