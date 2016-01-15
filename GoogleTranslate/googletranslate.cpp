#include "googletranslate.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>
#include <QAxObject>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>

const QString en_ru =
  "https://translate.google.com/translate_a/t?client=t&sl=Rus&tl=En&text=";

const QString ru_en =
  "https://translate.google.com/translate_a/t?client=t&sl=Rus&tl=En&text=";

class GOOGLETRANSLATESHARED_EXPORT GoogleTranslate: public Action {
private:
  QNetworkAccessManager *manager;
  QStringList keys;
public:
  GoogleTranslate() {
    manager = new QNetworkAccessManager();
    keys << "!tr" << "!translate" << "!переведи" << "!тр";
  }
  ~GoogleTranslate() {
    delete manager;
    manager = NULL;
  }

  QString getName() {
    return "Google Translate";
  }

  QStringList getKeys() {
    return keys;
  }

  QString getInfo() {
    return "Translator v0.1\nUse google without API so it's can be wrong)";
  }

  void execute(QAxObject *msg) {
    const QString text = msg->dynamicCall("Body()").toString();
    const QString word = text.left(text.indexOf(' ')).toLower();
    if(keys.contains(word)) {
      QUrl url(en_ru + text.mid(text.indexOf(' ')));
      QNetworkReply *reply = manager->get(QNetworkRequest(url));
      QEventLoop loop;
      QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
      QTimer timer;
      QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
      timer.start(2000);
      loop.exec();
      if(reply->error() == QNetworkReply::NoError) {
        const QString result = reply->readAll();
        const int start = result.indexOf('\"') + 1;
        const int end = result.indexOf('\"', start + 1);
        const QString tr = result.mid(start, end - start);
        msg->querySubObject("Chat()")->dynamicCall("SendMessage(QString)", tr);
      }
    }
  }
};

Action *createAction() {
  return new GoogleTranslate;
}

