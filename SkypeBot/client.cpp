#include "client.h"
#include <QAxObject>



Client::Client(QAxObject *obj, QObject *parrent):
    QObject(parrent),
    com(obj)
{
}

Client::~Client()
{
    delete com;
}
