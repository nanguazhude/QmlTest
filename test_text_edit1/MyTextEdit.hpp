#pragma once 

#include <QtQml/qqmlcomponent.h>
#include <QtQuick/qquickitem.h>
#include <QtGui/qtextdocument.h>
#include <QtGui/qabstracttextdocumentlayout.h>
#include <QtCore/qpointer.h>

class MyTextEditAdder :public QObject {
    Q_OBJECT
public:
    MyTextEditAdder(QObject * /**/ = nullptr);
    class BackGroundItemFormat {};
    class TextFrameFormat :
        public QTextFrameFormat,
        public BackGroundItemFormat {
    public:
    };
private:
    using Super = QObject;
};

class MyTextEdit : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QQmlComponent * textEdit READ getTextEdit WRITE setTextEdit NOTIFY textEditChanged)
    Q_PROPERTY(QQmlComponent * textFrameDelegate READ getTextFrameDelegate WRITE setTextFrameDelegate NOTIFY textFrameDelegateChanged)
private:
public:
    MyTextEdit(QQuickItem *parent = nullptr);
public:
    QQmlComponent * getTextEdit() const { return _text_edit_component; }
    void setTextEdit(QQmlComponent * arg);
    Q_SIGNAL void textEditChanged();
public:
    QQmlComponent * getTextFrameDelegate() const { return _text_frame_delegate; }
    void setTextFrameDelegate(QQmlComponent *);
    Q_SIGNAL void textFrameDelegateChanged();
public:
    using TextFrameFormat = MyTextEditAdder::TextFrameFormat;
    QTextFrame * create_frame(const TextFrameFormat &);
public:
    QTextDocument * getTextDocument() const { return _text_edit_document; }
    QQmlEngine * getQQmlEngine() const;
    QQuickItem * getTextEditObject() const { return _text_edit; }
public:
    static MyTextEditAdder * qmlAttachedProperties(QObject *object);
private:
    using Super = QQuickItem;
    QQmlComponent * _text_edit_component = nullptr;
    QQuickItem * _text_edit = nullptr;
    void _create_text_edit_object();
    QTextDocument * _text_edit_document = nullptr;
    QAbstractTextDocumentLayout * _layout_text_edit_document = nullptr;
    QQmlComponent * _text_frame_delegate = nullptr;
signals:
    void q_contentsChange(int, int, int);
};

class MyTextEditFrame : public QObject {
    Q_OBJECT
private:
    QRectF _old_rect;
    QRectF _rect;
    QPointer< MyTextEditAdder > _adder;
public:
    MyTextEditFrame(const QRectF & arg, QObject * p) :_rect(arg), QObject(p) {}
    constexpr static const char * textEditFramePropertyName() { return "\xF3""\xF2""\xF1" "texteditframe"; }
    Q_SIGNAL void frameRectChanged(const QRectF &);
    void updateFrameRect(const QRectF & arg) {
        if (arg == _rect) { return; }
        _rect = arg;
        frameRectChanged(_rect);
    }
    bool isRectChaned(const QRectF &arg) {
        if (_old_rect == arg) { return false; }
        _old_rect = arg;
        return true;
    }
    inline MyTextEditAdder * getAttached() const { return _adder.data(); }
    void setAttached(MyTextEditAdder * arg) { _adder = arg; }
};

QML_DECLARE_TYPEINFO(MyTextEdit, QML_HAS_ATTACHED_PROPERTIES)
 



