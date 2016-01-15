#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
class QAxObject;

class Client: public QObject{
    Q_OBJECT
public:
    explicit Client(QAxObject *obj,QObject *parrent = 0);
    ~Client();
private:
    QAxObject *com;
};

#endif // CLIENT_H
