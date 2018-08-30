#ifndef MYTESTEDIT_HPP
#define MYTESTEDIT_HPP

#include <QtQml/qqmlcomponent.h>
#include <QtQuick/qquickitem.h>
#include <QtGui/qtextdocument.h>
#include <QtGui/qabstracttextdocumentlayout.h>

class MyTextEditFrame : public QObject {
    Q_OBJECT
private:
    QRectF _rect;
public:
    MyTextEditFrame(const QRectF & arg,QObject * p):_rect(arg),QObject(p) {}
    constexpr static const char * textEditFramePropertyName() { return "\xF3""\xF2""\xF1" "texteditframe"; }
    Q_SIGNAL void frameRectChanged(const QRectF &);
    void updateFrameRect(const QRectF & arg) { 
        if (arg == _rect) { return; }
        _rect = arg;
        frameRectChanged(_rect);
    }
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
    class BackGroundItemFormat {};
    class TextFrameFormat : public QTextFrameFormat, public BackGroundItemFormat {};
    QTextFrame * create_frame(const TextFrameFormat &);
private:
    using Super = QQuickItem;
    QQmlComponent * _text_edit_component = nullptr;
    QQuickItem * _text_edit = nullptr;
    void _create_text_edit_object();
    QTextDocument * _text_edit_document = nullptr;
    QAbstractTextDocumentLayout * _layout_text_edit_document = nullptr;
    QQmlComponent * _text_frame_delegate = nullptr;
};

#endif // MYTESTEDIT_HPP



