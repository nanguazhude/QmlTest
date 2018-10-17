#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtQuick>

#include "Window.hpp"
#include "QuickWindow.hpp"
#include "MainThreadGLWindow.hpp"

int main(int argc, char ** argv) {

    QApplication varApp{ argc,argv };
    QDir::setCurrent(varApp.applicationDirPath());

    //MainThreadGLWindow varWindows1;
    //varWindows1.show();

    //auto varWindow = new RootWindow ;
    //QWidget::createWindowContainer(varWindow)->show();

    //QuickWindow xxw{ nullptr };
    //xxw.show();

    MainThreadGLWindow varWindows1;
    {
        auto varWindow = new QuickWindow(&varWindows1);
        varWindows1.setContent(varWindow);
    }
    varWindows1.resize(512,512);
    varWindows1.show();
        
    return varApp.exec();

}





















