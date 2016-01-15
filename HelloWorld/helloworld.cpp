#include "helloworld.h"
#include <QAxObject>


class HELLOWORLDSHARED_EXPORT HelloWorld: public Action {

public:
  HelloWorld();
  QString getName() ;
  QStringList getKeys() ;
  QString getInfo() ;
  void execute(QAxObject *) ;
private:
  QMap<QString, QString> map;
};

HelloWorld::HelloWorld() {
  map["!hi bot"] = "Hi!";
  map["!hello bot"] = "Hello :)";
  map["!привет бот"] = "Приветики)";
  map["!ку бот"] = "Не кукай, ёпты! Дарова)";
}

QString HelloWorld::getName() {
  return "HelloWorld[0.1]";
}

QStringList HelloWorld::getKeys() {
  return map.keys();
}

QString HelloWorld::getInfo() {
  return "Very simple hello world plugin^_^";
}

void HelloWorld::execute(QAxObject *msg) {
  const QString text = msg->dynamicCall("Body()").toString();
  if(map.contains(text.toLower())) {
    msg->querySubObject("Chat()")->dynamicCall("SendMessage(QString)", map[text.toLower()]);
  }
}

Action *createAction() {
  return new HelloWorld;
}

