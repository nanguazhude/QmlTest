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

    {
        auto varRequest = new sstd::RequestTextItem;
        varRequest->setHtmlTitle(QStringLiteral(R"__(<p ><font size="6" color="blue">Hellow</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="3" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varRequest->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varRequest);
    }

    {
        auto varReply = new sstd::ReplyTextItem;
        varReply->setHtmlTitle(QStringLiteral(R"__(<p><font size="6" color="red">World</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="3" color="black">j j</font></p>)"));
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="3" color="black">jjj j</font></p>)"));
        varReply->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varReply);
    }

    {
        auto varRequest = new sstd::RequestTextItem;
        varRequest->setHtmlTitle(QStringLiteral(R"__(<p ><font size="6" color="blue">Hellow</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="14" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="14" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="14" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varRequest->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varRequest);
    }

    {
        auto varReply = new sstd::ReplyTextItem;
        varReply->setHtmlTitle(QStringLiteral(R"__(<p><font size="6" color="red">World</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="14" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="14" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varHtmlData.push_back(QStringLiteral(R"(<p ><font size="14" color="black">jjj jj jjjj jj jjjjj jjj</font></p>)"));
        varReply->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varReply);
    }

    varTextBrowser.show();
    
    return varApp.exec();
}






