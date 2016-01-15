#ifndef ACTION_GLOBAL_H
#define ACTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ACTION_LIBRARY)
#  define ACTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ACTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ACTION_GLOBAL_H
