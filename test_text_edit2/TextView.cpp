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
            intersects(varTextDocumentRect)==false) {
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
        varAns.reserve(1+ varLast.size() + varPre.size() );

        varPre.push_back( varBlock );
        varPre.merge(std::move(varLast));

        varAns.assign(std::make_move_iterator(varPre.begin()),
            std::make_move_iterator(varPre.end()));

        return std::move(varAns);
    }

}/****/

TextItem::TextItem(QObject * arg) :Super(arg) {

}

TextDocumentLayout::TextDocumentLayout(QTextDocument *arg) : Super(arg) {

}

TextDocument::TextDocument(QObject *arg) : Super(arg) {
    this->setDocumentLayout(new TextDocumentLayout{ this });
}

TextBrowser::TextBrowser(QWidget * arg) : Super(arg) {
    this->setDocument(new TextDocument{ this });
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
    painter->setBrush(QColor(10, 20, 189, 255));
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








