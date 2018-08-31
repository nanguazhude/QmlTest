#include <cassert>
#include "MyTextEdit.hpp"
#include <QtCore/qdebug.h>
#include <QtGui/qtextcursor.h>
#include <QtQuick/qquicktextdocument.h>
#include <private/qtextdocumentlayout_p.h>
#include <limits>

namespace {

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
                varWith = std::max(varWith,varLine.naturalTextWidth());
            }
        } while (false);
        return varWith;
    }

    class MyTextDocumnetLayout : public QTextDocumentLayout {
        using Super = QTextDocumentLayout;
    public:
        MyTextDocumnetLayout(QTextDocument * parent) : Super(parent) {}
        QRectF frameBoundingRect(QTextFrame *frame) const override {

            const auto varFrameBoundingRect = Super::frameBoundingRect(frame);
            auto varTextEditFrame = dynamic_cast<MyTextEditFrame*>(
                frame->property(MyTextEditFrame::textEditFramePropertyName()).value<QObject *>());

            if (nullptr == varTextEditFrame) {
                return varFrameBoundingRect;
            }

            double varWith = std::min(varFrameBoundingRect.width(), 10.0);
            {
                auto varPos = frame->begin();
                const auto varE = frame->end();
                for (; varPos != varE; ++varPos) {
                    varWith = std::max(varWith, getMaxWidth(varPos.currentBlock()));
                }
            }

            auto varUpdateRect = varFrameBoundingRect;

            {
                const auto varFrameFormat = frame->frameFormat();
                const auto varX = varFrameFormat.leftMargin() + (varFrameFormat.padding());
                varUpdateRect.moveLeft(varX);
                varUpdateRect.setWidth(std::max(10.0,varWith  ));
            }

            varTextEditFrame->updateFrameRect(varUpdateRect);

            return varFrameBoundingRect;
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
    _layout_text_edit_document = new MyTextDocumnetLayout(_text_edit_document);
    _text_edit_document->setDocumentLayout(_layout_text_edit_document);
    /************************************************/
    connect(_layout_text_edit_document, &QAbstractTextDocumentLayout::documentSizeChanged,
        _text_edit, [this](const QSizeF & arg) {
        //this->setWidth(arg.width());
        this->setHeight(arg.height());
    });
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

