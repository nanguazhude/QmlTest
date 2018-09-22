#pragma once

#include "test_library_0_global.hpp"
#include <QtCore/qobject.h>
#include <QTextBlockUserData> 

class SSTD_LIBRARY_EXPORT ClassA : 
    public QObject,public QTextBlockUserData
{
public:
    ClassA();
    virtual ~ClassA();
};

extern "C" {
    SSTD_LIBRARY_EXPORT QObject * createTestObject();
}

