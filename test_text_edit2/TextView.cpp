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

namespace sstd {

    namespace {

        class UpdateEvent : public QEvent {
        public:
            UpdateEvent() :Super(QEvent::User) {}
        private:
            using Super = QEvent;
        };

        class RelayoutGifEvent : public UpdateEvent {
            QPointer<TextDocumentLayout> $m$Count;
        public:

            RelayoutGifEvent(TextDocumentLayout * arg) :$m$Count(arg) {
                ++(arg->$m$RelayoutEventCount);
            }

            ~RelayoutGifEvent() {
                auto var = $m$Count.data();
                if (var) { --(var->$m$RelayoutEventCount); }
            }

        };

        /*获得可见区域对应的viewport*/
        inline QRect mapToViewport(const TextBrowser * arg) {
            auto varSize = arg->size();
            auto varVB = arg->verticalScrollBar();
            auto varHB = arg->horizontalScrollBar();
            varSize.setWidth(varSize.width() + 1);
            varSize.setHeight(varSize.height() + 1);
            return{ QPoint(varHB->value() ,varVB->value()),varSize };
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
    //#define TESTTEXTBROWSER
#if defined(TESTTEXTBROWSER)

        class xTextItem : public TextItem {
        public:
            QTextFrameFormat $m$TextFrameFormat;
            QTextFrameFormat getTextFrameFormat() const override { return $m$TextFrameFormat; }
            QList<QString> getHtmlData() const override {
                return QList<QString>() <<
                    QString(QStringLiteral(R"___(
<p>
    <font size="17" color="purple">%1:today is a fine day!</font>
</p>
)___")).arg(1 + (std::rand() & 3)) << QStringLiteral(R"(
<p>
    sdf lds ajf lweh aofi ewah<img src= ":/gif/myqml/cat.gif" />
</p> )"
);

            }
        };

        for (int i = 0; i < 100; ++i) {
            varDocument->appendTextFrame(new xTextItem);
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

    QTextFrame * TextDocument::appendTextFrame(TextItem * arg) {
        QTextFrame * varAns = nullptr;

        {/*首先插入一个Frame*/
            QTextCursor varTC{ this->rootFrame() };
            varTC.movePosition(QTextCursor::End);
            varAns = varTC.insertFrame(arg->getTextFrameFormat());
            TextItem::setTextItem(varAns, arg);
        }

        do {/*插入Html*/
            QTextCursor varTC{ varAns };
            const auto varHtmls = arg->getHtmlData();
            if (varHtmls.empty()) { break; }
            auto varPos = varHtmls.begin();
            varTC.insertHtml(*varPos);
            const auto varEndPos = varHtmls.end();
            for (++varPos; varPos != varEndPos; ++varPos) {
                varTC.insertBlock();
                varTC.insertHtml(*varPos);
            }
        } while (false);

        return varAns;
    }

    /*此函数实现绘制GIF*/
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

        /*载入Movie*/
        insertMovie(varImageName);

        auto varMovie = $m$MovieCache.object(varImageName);
        if (varMovie == nullptr) {
            /*载入图片失败*/
            painter->setPen(QPen(QColor(111, 112, 113, 200), 1));
            painter->setBrush(QColor(std::rand() & 127, std::rand() & 127, std::rand() & 127, 200));
            painter->drawRect(rect);
            return;
        }
        else {
            /*绘制图片*/
            const QImage varImage = varMovie->currentImage();
            painter->drawImage(rect, varImage);
            return;
        }

    }

    /*如果布局变更，更新Layout*/
    void TextDocumentLayout::positionInlineObject(
        QTextInlineObject item,
        int posInDocument,
        const QTextFormat &format) {
        Super::positionInlineObject(item, posInDocument, format);
        if (format.isImageFormat() == false) { return; }
        auto varImageCharFormat = format.toImageFormat();
        auto varImageName = varImageCharFormat.name();
        if (false == varImageName.endsWith(QStringLiteral(".gif"),
            Qt::CaseInsensitive)) {
            return;
        }
        tryRelayoutGifObjects(0);
    }

    /*
    如果大小改变，更新Layout
    如果此函数逻辑错误，则可能导致GIF图片更新失败
    */
    void TextDocumentLayout::resizeInlineObject(
        QTextInlineObject item,
        int posInDocument,
        const QTextFormat &format) {
        Super::resizeInlineObject(item, posInDocument, format);
        if (format.isImageFormat() == false) { return; }
        auto varImageCharFormat = format.toImageFormat();
        auto varImageName = varImageCharFormat.name();
        if (false == varImageName.endsWith(QStringLiteral(".gif"),
            Qt::CaseInsensitive)) {
            return;
        }

        {/*在当前布局中搜索此项，如果找到则返回，否则尝试重新布局*/
            auto varPos = $m$GifItemLayoutData.find(varImageName);
            if (varPos == $m$GifItemLayoutData.end()) {
                auto varInsertData = $m$GifItemLayoutData.try_emplace(varImageName);
                varInsertData.first->second.emplace(posInDocument, varImageName);
                tryRelayoutGifObjects(0);
                return;
            }
            if (varPos->second.count(posInDocument) < 1) {
                varPos->second.emplace(posInDocument, varImageName);
                tryRelayoutGifObjects(0);
                return;
            }
        }

    }

    bool TextDocumentLayout::event(QEvent * e) {
        if (dynamic_cast<RelayoutGifEvent*>(e)) {
            e->accept();
            relayoutGifObjects();
            return true;
        }
        return Super::event(e);
    }

    void TextDocumentLayout::tryRelayoutGifObjects(int argSelect) {

        if ($m$RelayoutEventCount > argSelect) {
            /*如果超出预期事件数量，则放弃调用*/
            return;
        }

        /*延迟1ms后发出事件*/
        $m$AboutPostEvent = std::make_unique<RelayoutGifEvent>(this);
        QTimer::singleShot(1, this, [this]() {
            if ($m$AboutPostEvent) {
                QCoreApplication::postEvent(this, $m$AboutPostEvent.release());
            }
        });

    }

    /*寻找可见区域内的GIF并缓存*/
    void TextDocumentLayout::relayoutGifObjects() {

        {/*每隔一段时间调用此函数，避免过于频繁的调用*/
            auto varCurrentTime = std::chrono::high_resolution_clock::now();
            if (std::chrono::abs(varCurrentTime - $m$LastGifLayoutTimeStamp) < 8ms) {
                tryRelayoutGifObjects(1);
                return;
            }
            $m$LastGifLayoutTimeStamp = varCurrentTime;
        }

        /*设置冗余缓存大小*/
        constexpr const static int varMinCost = 16;

        /*获得可见QTextBlock*/
        auto varVisibleBlock = getVisibleBlocks($m$TextBrowser);
        if (varVisibleBlock.empty()) {
            $m$GifItemLayoutData.clear();
            $m$MovieCache.setMaxCost(varMinCost);
            return;
        }

        {/*在可见QTextBlock里面寻找GIF*/
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
        }

        /*更新缓存区大小*/
        $m$MovieCache.setMaxCost(static_cast<int>(varMinCost + $m$GifItemLayoutData.size()));

        /*立即进行一次绘制*/
        auto varViewPort = this->$m$TextBrowser->viewport();
        if (varViewPort) { varViewPort->update(); }

        return;
    }

    void TextDocumentLayout::insertMovie(const QString & arg) {
        if (arg.isEmpty()) { return; }
        auto varMovie = $m$MovieCache.object(arg);
        if (varMovie) { return; }

        varMovie = new GifMovie(arg);

        /*变帧的时候更新内容*/
        connect(varMovie, &QMovie::frameChanged,
            this, [varMovieName = arg, this](int) { updateMovie(varMovieName); },
            Qt::QueuedConnection);
        varMovie->start();

        if (varMovie->isValid() == false) {
            varMovie->stop();
            varMovie->deleteLater();
            qDebug() << (QStringLiteral("can not load : ") + arg);
            return;
        }

        /*销毁的时候尝试更新缓存大小*/
        connect(varMovie, &QObject::destroyed,
            this, [this]() {tryRelayoutGifObjects(0); },
            Qt::QueuedConnection);

        /*插入缓存*/
        $m$MovieCache.insert(arg, varMovie, 1);

        /*如果缓存不够大，尝试扩充它*/
        if ($m$MovieCache.maxCost() >= $m$MovieCache.totalCost()) {
            tryRelayoutGifObjects(0);
        }

    }

    GifMovie::GifMovie(const QString & arg) {
        this->setCacheMode(QMovie::CacheAll);
        this->setFileName(arg);
    }

    void TextDocumentLayout::updateMovie(const QString & arg) {

        auto varUpdatePosition = $m$GifItemLayoutData.find(arg);
        if (varUpdatePosition == $m$GifItemLayoutData.end()) {
            return;
        }

        auto varDocument = $m$TextBrowser->document();

        std::set<QTextBlock> varData;
        auto & varPos = varUpdatePosition->second;
        for (const auto & varP : varPos) {
            varData.insert(varDocument->findBlock(varP.posInDocument));
        }

        if (varData.empty()) { return; }

        for (const auto & varB : varData) {
            if (false == varB.isValid()) {
                continue;
            }
            this->updateBlock(varB);
        }

    }

    QTextFrame * TextBrowser::appendTextFrame(TextItem*arg) {
        return static_cast<TextDocument *>(document())
            ->appendTextFrame(arg);
    }

}/*namespace sstd*/

