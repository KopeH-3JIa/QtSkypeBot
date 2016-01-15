#ifndef GOOGLETRANSLATE_GLOBAL_H
#define GOOGLETRANSLATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GOOGLETRANSLATE_LIBRARY)
#  define GOOGLETRANSLATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define GOOGLETRANSLATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GOOGLETRANSLATE_GLOBAL_H