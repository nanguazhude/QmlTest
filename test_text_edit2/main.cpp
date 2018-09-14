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

    {
        auto varRequest = new sstd::RequestTextItem;
        varRequest->setHtmlTitle(QStringLiteral(R"__(<p ><font size="6" color="blue">Hellow</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(
<p >
    <font size="3" color="black">j</font>
    <img src=":/image/myqml/i_f06.png" />
    <img src=":/image/myqml/i_f16.png" />
    <img src=":/image/myqml/i_f25.png" />
</p>)"));
        varRequest->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varRequest);
    }

    {
        auto varReply = new sstd::ReplyTextItem;
        varReply->setHtmlTitle(QStringLiteral(R"__(<p><font size="6" color="red">World</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(
<p >
    <font size="3" color="black">j</font>
    <img src=":/image/myqml/i_f16.png" />
    <img src=":/image/myqml/i_f25.png" />
    <img src=":/image/myqml/i_f06.png" />
</p>)"));
        varReply->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varReply);
    }
    
    {
        auto varRequest = new sstd::RequestTextItem;
        varRequest->setHtmlTitle(QStringLiteral(R"__(<p ><font size="6" color="blue">Hellow</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(
<p >
    <font size="3" color="black">j</font>
    <img src=":/gif/myqml/003.gif" />
    <img src=":/gif/myqml/006.gif" />
    <img src=":/gif/myqml/009.gif" />
</p>)"));
        varRequest->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varRequest);
    }

    {
        auto varReply = new sstd::ReplyTextItem;
        varReply->setHtmlTitle(QStringLiteral(R"__(<p><font size="6" color="red">World</font></p>)__"));
        QList<QString> varHtmlData;
        varHtmlData.push_back(QStringLiteral(R"(
<p >
    <font size="3" color="black">j</font>
    <img src=":/gif/myqml/012.gif" />
    <img src=":/gif/myqml/015.gif" />
    <img src=":/gif/myqml/018.gif" />
</p>)"));
        varReply->setHtmlData(std::move(varHtmlData));
        varTextBrowser.appendTextFrame(varReply);
    }

    varTextBrowser.show();
    
    return varApp.exec();
}






