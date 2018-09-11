#include <chrono>
using namespace std::chrono_literals;

#include "PrivateTextView.hpp"
#include "TextView.hpp"

TextItem::TextItem(QObject * arg):Super(arg) {
    
}

TextDocumentLayout::TextDocumentLayout(QTextDocument *arg):Super(arg) {

}

TextDocument::TextDocument(QObject *arg):Super(arg) {
    this->setDocumentLayout(new TextDocumentLayout{this});
}

TextBrowser::TextBrowser(QWidget * arg) :Super(arg){

}













