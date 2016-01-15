#ifndef IACTION
#define IACTION

#include <QString>
#include "action_global.h"

class QAxObject;

class ACTIONSHARED_EXPORT Action
{
public:
    virtual ~Action(){}
    virtual QString getName() = 0;
    virtual QStringList getKeys() = 0;
    virtual QString getInfo() = 0;
    virtual void execute(QAxObject *) = 0;
};

#endif // IACTION

