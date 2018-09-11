#include <chrono>
using namespace std::chrono_literals;

#include <QtCore/qpointer.h>
#include <QtGui/qpainter.h>

#include "PrivateTextView.hpp"
#include "TextView.hpp"

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

    painter->setPen(QPen(QColor(255,0,0,255)));
    painter->setBrush(QColor(10,20,189,255));
    painter->drawRect(rect);

    (void)frame;
    (void)fd;
    (void)clip;
}










