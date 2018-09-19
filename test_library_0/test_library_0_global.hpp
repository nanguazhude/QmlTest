#pragma once

#include <QtCore/qglobal.h>

#if defined(SSTD_LIBRARY_DLL)
#define SSTD_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#define SSTD_LIBRARY_EXPORT Q_DECL_IMPORT
#endif












