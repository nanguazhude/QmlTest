#pragma once

#include <QtWidgets/qtextbrowser.h>

class TextBrowser : public QTextBrowser {
    Q_OBJECT
public:
    TextBrowser(QWidget *parent = nullptr);
private:
    using Super = QTextBrowser;
    
};














