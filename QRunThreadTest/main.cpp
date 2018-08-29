#include "MainWindow.hpp"
#include <QApplication>
#include <QtCore/qdebug.h>

#include "QRunThread.hpp"
#include <QtCore/qthread.h>
#include <iostream>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    sstd::QRunThread::construct();

    MainWindow window;

    {/*test main thread*/
        sstd::QRunThread mainThread(nullptr);
        mainThread.run([]() {std::cout << "Hellow Main Thread!" << std::endl; });
        mainThread.atDestory([]() {std::cout << "Hellow Main Thread! @ destory" << std::endl; });
        qDebug() << (qApp->thread() == mainThread.getThread());
        qDebug() << (mainThread.getRunThread(mainThread.getThread()) == mainThread);
    }

    {/*test new thread*/
        sstd::QRunThread newThread{};
        newThread.run([]() {std::cout << "Hellow New Thread!" << std::endl; });
        newThread.atDestory([]() {std::cout << "Hellow New Thread! @ destory" << std::endl; });
        qDebug() << (qApp->thread() == newThread.getThread());
        qDebug() << (newThread.getRunThread(newThread.getThread()) == newThread);
        newThread.setQRunThread(&window);
    }

    {
        sstd::QRunThread newThread{};
        newThread.run([]() {
            sstd::QRunThread newThread{};
            newThread.run([]() {std::cout << "Hellow New Thread! : 2" << std::endl; });
            newThread.atDestory([]() {std::cout << "destory @ 2" << std::endl; });
        });
    }

    window.show();

    return app.exec();
}
