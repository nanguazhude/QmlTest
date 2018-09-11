#pragma once

#include <QtWidgets/qapplication.h>

class Application : public QApplication{
    Q_OBJECT
public:
    Application(int &argc, char **argv);
private:
    using Super = QApplication;
};


