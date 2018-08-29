#include "sstdqml_plugin.hpp"
#include "MyRectangle.hpp"

#include <qqml.h>

void SSTDQmlPlugin::registerTypes(const char *uri){
    /*uri:SSTDQml*/
    qmlRegisterType<MyRectangle>(uri, 1, 0, "MyRectangle");
}



