#include <cassert>
#include "MyTextEdit.hpp"
#include <QtCore/qdebug.h>
#include <QtGui/qtextcursor.h>
#include <QtQuick/qquicktextdocument.h>
#include <private/qtextdocumentlayout_p.h>
#include <private/qquickanimatedimage_p.h>
#include <limits>
#include <QtCore/qtimer.h>
#include <QtQuick>
#include <chrono>
using namespace std::chrono_literals;

class MyTextEdit;
namespace {

    /*void q_contentsChange(int, int, int);*/
    class MyTextDocumnetLayout : public QTextDocumentLayout {
        using Super = QTextDocumentLayout;

        bool $m$IsDraw = false;
        MyTextEdit * $m$Editor = nullptr;

        inline double getMaxWidth(const QTextBlock & varBlock) const {
            double varWith = 0;
            do {
                if (varBlock.isValid() == false) { break; }
                if (varBlock.lineCount() < 1) { break; }
                const auto varLayout = varBlock.layout();
                /*********************************************************/
                if constexpr (false) {
                    static unsigned int n = 0;
                    auto varBlockPos = varBlock.begin();
                    for (; !(varBlockPos.atEnd()); ++varBlockPos) {

                        const auto & varFragment = varBlockPos.fragment();
                        const auto & varCharFormat = varFragment.charFormat();
                        if (varCharFormat.isImageFormat() == false) { continue; }
                        auto varImageFormat = varCharFormat.toImageFormat();

                        qDebug() << varImageFormat.name();

                        const auto varImageNameNew =
                            QStringLiteral("image://GifImage/myqml/test_text_edit1/cat.gif")
                            + QString::number(++n);
                        varImageFormat.setName(varImageNameNew);

                        if ((varFragment.position() < 200) && (varFragment.position() > 100)) {
                            //qDebug() << varEditor->getTextDocument();
                            QTextCursor varTC{ $m$Editor->getTextDocument() };
                            //qDebug() << varFragment.position();
                            varTC.setPosition(varFragment.position(), QTextCursor::MoveAnchor);
                            varTC.setPosition(varFragment.position() + 1, QTextCursor::KeepAnchor);
                            //varTC.setCharFormat(varImageFormat);
                            //qDebug() << varTC.charFormat().isImageFormat();
                            //qDebug() <<  varTC.charFormat() ;
                            varTC.setCharFormat(varImageFormat);
                            //qDebug() << varFragment.position();
                        }
                        //varEditor->q_contentsChange(varFragment.position(), 0, varFragment.length());
                        //varEditor->q_contentsChange(varFragment.position(), varFragment.length(), 0);
                    }/*for:*/
                }
                /*********************************************************/
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

    public:
         
        const constexpr static int $m$Timer = -8564;
        MyTextDocumnetLayout(QTextDocument * parent, MyTextEdit * edit) :
            Super(parent),
            $m$Editor(edit) {}

        void timerEvent(QTimerEvent *event) override {
            if (event->timerId()==$m$Timer) {
                event->accept();
                auto varTime = std::chrono::high_resolution_clock::now();
                if (std::chrono::abs(varTime - $m$Time) > 8ms) {
                    $m$Time = std::chrono::high_resolution_clock::now();
                    this->updateGif();
                }
                else {
                    QCoreApplication::postEvent(this, new QTimerEvent($m$Timer));
                }
                return;
            }
            return Super::timerEvent(event);
        }

        std::chrono::high_resolution_clock::time_point $m$Time;
        void positionInlineObject(QTextInlineObject item, int posInDocument, const QTextFormat &format) override {
            Super::positionInlineObject(item, posInDocument, format);
            $m$Time = std::chrono::high_resolution_clock::now();
            QCoreApplication::postEvent(this,new QTimerEvent($m$Timer));
        }

        void resizeInlineObject(QTextInlineObject item, int posInDocument, const QTextFormat &format) override {
            Super::resizeInlineObject(item, posInDocument, format);
            $m$Time = std::chrono::high_resolution_clock::now();
            QCoreApplication::postEvent(this, new QTimerEvent($m$Timer));
        }

        /******/
        QRectF frameBoundingRect(QTextFrame *frame) const override {

            const auto varFrameBoundingRect = Super::frameBoundingRect(frame);
            auto varTextEditFrame = dynamic_cast<MyTextEditFrame*>(
                frame->property(MyTextEditFrame::textEditFramePropertyName()).value<QObject *>());

            if (nullptr == varTextEditFrame) {
                return varFrameBoundingRect;
            }

            if ($m$IsDraw) {
                return varFrameBoundingRect;
            }

            class ThisCallLock {
                MyTextDocumnetLayout * $m$;
            public:
                ThisCallLock(MyTextDocumnetLayout*a) :$m$(a) { $m$->$m$IsDraw = true; }
                ~ThisCallLock() { $m$->$m$IsDraw = false; }
            }varLock{ const_cast<MyTextDocumnetLayout *>(this) };


            /*加快程序运行速度*/
            if (varTextEditFrame->isRectChaned(varFrameBoundingRect) == false) {
                return varFrameBoundingRect;
            }

            double varWith = std::min(varFrameBoundingRect.width(), 10.0);
            {
                auto varPos = frame->begin();
                const auto varE = frame->end();
                for (; varPos != varE; ++varPos) {
                    varWith = std::max(varWith, this->getMaxWidth(varPos.currentBlock()));
                }
            }

            auto varUpdateRect = varFrameBoundingRect;

            {
                const auto varFrameFormat = frame->frameFormat();
                const auto varX = varFrameFormat.leftMargin() + (varFrameFormat.padding());
                varUpdateRect.moveLeft(varX);
                varUpdateRect.setWidth(std::max(10.0, varWith));
            }

            varTextEditFrame->updateFrameRect(varUpdateRect);

            return varFrameBoundingRect;
        }

        std::map<int, QQuickItem*> $m$Items;

        void updateGif() {
            auto varDocument = $m$Editor->getTextDocument();
            auto varBlock = varDocument->firstBlock();

            std::map<int, QQuickItem*> varItems;

            while (varBlock.isValid()) {
                const auto varCurrentBlock = varBlock;
                varBlock = varBlock.next();

                auto varBlockPos = varCurrentBlock.begin();
                for (; !(varBlockPos.atEnd()); ++varBlockPos) {

                    const auto & varFragment = varBlockPos.fragment();
                    const auto & varCharFormat = varFragment.charFormat();
                    if (varCharFormat.isImageFormat() == false) { continue; }
                    auto varImageFormat = varCharFormat.toImageFormat();
                    if (varImageFormat.name().endsWith(QStringLiteral(".gif"), Qt::CaseInsensitive)) {
                    }
                    else {
                        continue;
                    }

                    const auto varPosition = varFragment.position() - varCurrentBlock.position();
                    const auto varLength = varFragment.length();

                    if (varCurrentBlock.layout()->isValidCursorPosition(varPosition)) {
                        const auto varBlockRect = this->blockBoundingRect(varCurrentBlock);
                        auto varLinePosition = varCurrentBlock.layout()->lineForTextPosition(varPosition);
                        int varCursor = varPosition;
                        auto varX = varLinePosition.cursorToX(&varCursor);
                        auto varBlockPosition = this->blockBoundingRect(varCurrentBlock);
                        QRectF varImageRect{
                            QPointF{ varX + varBlockPosition.topLeft().x(),
                            varLinePosition.position().y() + varBlockPosition.topLeft().y()},
                            QSizeF{ varImageFormat.width(),varImageFormat.height()}
                        };

                        auto pos = $m$Items.find(varFragment.position());
                        if (pos == $m$Items.end()) {
                            QQmlComponent varContex{ $m$Editor->getQQmlEngine() , "myqml/test_text_edit1/cat_gif.qml" };
                            auto varAImage = varContex.beginCreate($m$Editor->getQQmlEngine()->rootContext());
                            varAImage->setParent($m$Editor);
                            static_cast<QQuickItem*>(varAImage)->setParentItem($m$Editor);
                            static_cast<QQuickItem*>(varAImage)->setPosition(varImageRect.topLeft());
                            static_cast<QQuickItem*>(varAImage)->setZ(-500);
                            varContex.completeCreate();
                            assert(varItems.count(varFragment.position()) == 0);
                            varItems.emplace(varFragment.position(), static_cast<QQuickItem*>(varAImage));
                        }
                        else {
                            pos->second->setPosition(varImageRect.topLeft());
                            varItems.insert($m$Items.extract(pos));
                        }

                        //qDebug() << varImageRect;
                    }
                    else {
                        qDebug() << "invalid position";
                    }

                }

            }

            /*立即清除*/
            for (const auto & varI : $m$Items) {
                varI.second->setVisible(false);
                varI.second->deleteLater();
            }

            $m$Items = std::move(varItems);

        }

    };

}/*namespace*/

MyTextEdit::MyTextEdit(QQuickItem * parent) : Super(parent) {

}

void MyTextEdit::setTextEdit(QQmlComponent *arg) {
    if (arg == _text_edit_component) { return; }
    if (_text_edit_component) {
        qDebug() << "can not change TextEdit";
        return;
    }
    _text_edit_component = arg;
    /*******************************/
    //创建TextEdit
    _create_text_edit_object();
    /*******************************/
    textEditChanged();
}

void MyTextEdit::_create_text_edit_object() {
    if (nullptr == _text_edit_component) { return; }
    auto varContext = _text_edit_component->creationContext();
    assert(varContext);
    /***************************************************/
    //创建TextEdit
    if (_text_edit) { delete _text_edit; }
    _text_edit = dynamic_cast<QQuickItem *>(_text_edit_component->beginCreate(varContext));
    assert(_text_edit);
    _text_edit->setParent(this);
    _text_edit->setParentItem(this);
    _text_edit_component->completeCreate();
    /***************************************************/
    auto varQuickTextDocument = _text_edit->property("textDocument").value<QQuickTextDocument*>();
    assert(varQuickTextDocument);
    _text_edit_document = varQuickTextDocument->textDocument();
    assert(_text_edit_document);
    _layout_text_edit_document = new MyTextDocumnetLayout(_text_edit_document, this);
    _text_edit_document->setDocumentLayout(_layout_text_edit_document);

    /************************************************/
    connect(_layout_text_edit_document, &QAbstractTextDocumentLayout::documentSizeChanged,
        _text_edit, [this](const QSizeF & arg) {
        //this->setWidth(arg.width());
        this->setHeight(arg.height());
    });
    /*********************************************/
    connect(this, SIGNAL(q_contentsChange(int, int, int)), _text_edit, SLOT(q_contentsChange(int, int, int)));
}


QQmlEngine * MyTextEdit::getQQmlEngine() const {
    return _text_edit_component->creationContext()->engine();
}

QTextFrame * MyTextEdit::create_frame(const TextFrameFormat & arg) {
    assert(_text_edit);
    assert(_text_edit_component);
    assert(_text_frame_delegate);

    QTextCursor varC{ _text_edit_document };
    varC.movePosition(QTextCursor::End);
    auto varFrame = varC.insertFrame(arg);

    /**********************************************/
    /*创建背景元素*/
    auto varTextEditFrame = new MyTextEditFrame{ {0,0,1,1}, varFrame };
    varFrame->setProperty(MyTextEditFrame::textEditFramePropertyName(),
        QVariant::fromValue<QObject*>(varTextEditFrame));
    auto varContext = _text_frame_delegate->creationContext();
    assert(varContext);
    auto varBackgroundItem = dynamic_cast<QQuickItem *>(_text_frame_delegate->beginCreate(varContext));
    varBackgroundItem->setParentItem(this);
    varBackgroundItem->setParent(varTextEditFrame);
    varBackgroundItem->setZ(-1000);
    connect(varTextEditFrame, &MyTextEditFrame::frameRectChanged,
        varBackgroundItem, [varBackgroundItem](const QRectF & arg) {
        varBackgroundItem->setX(arg.x());
        varBackgroundItem->setY(arg.y());
        varBackgroundItem->setWidth(arg.width());
        varBackgroundItem->setHeight(arg.height()); });
    /****************************/
    //set append data
    auto varAppendData = /*try read append data*/
        dynamic_cast<MyTextEditAdder *>(qmlAttachedPropertiesObject<MyTextEdit>(varBackgroundItem, false));
    if (varAppendData == nullptr) { /*if appened data is null*/
        varAppendData = /*create the appened data*/
            dynamic_cast<MyTextEditAdder *>(qmlAttachedPropertiesObject<MyTextEdit>(varBackgroundItem, true));
    }
    assert(varAppendData);
    varTextEditFrame->setAttached(varAppendData);
    /****************************/
    _text_frame_delegate->completeCreate();
    /**********************************************/

    return varFrame;
}

void MyTextEdit::setTextFrameDelegate(QQmlComponent * arg) {
    if (arg == _text_frame_delegate) { return; }
    if (_text_frame_delegate) {
        qDebug() << "can not change TextFrameDelegate";
        return;
    }
    _text_frame_delegate = arg;
    textFrameDelegateChanged();
}

MyTextEditAdder::MyTextEditAdder(QObject * arg) :Super(arg) {

}

MyTextEditAdder * MyTextEdit::qmlAttachedProperties(QObject *object) {
    return new MyTextEditAdder(object);
}

