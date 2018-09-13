#include <QtGui>
#include <QtCore>
#include <QtWidgets>

#include "Application.hpp"
#include "TextView.hpp"
#include "RequestTextItem.hpp"
#include "ReplyTextItem.hpp"

int main(int argc,char ** argv) {
    Application varApp{argc,argv};

    sstd::TextBrowser varTextBrowser;
    varTextBrowser.resize(512,512);
    varTextBrowser.show();
    
    return varApp.exec();
}






