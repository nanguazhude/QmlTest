#include <QtGui>
#include <QtCore>
#include <QtWidgets>

#include "Application.hpp"
#include "Window.hpp"

int main(int argc,char ** argv) {
    Application varApp{argc,argv};

    Window window;
    window.show();
    
    return varApp.exec();
}








