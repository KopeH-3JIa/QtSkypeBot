#include "skype.h"
#include "client.h"
#include <QDebug>

Skype::Skype(QObject *parent) :
    QAxObject("Skype4COM.Skype",parent),
    client(new Client(this->querySubObject("Client")))
{
    connect(this, SIGNAL(MessageStatus(IDispatch*, TChatMessageStatus)),
            this, SLOT(slotMessageSkype(IDispatch*, TChatMessageStatus)));
}

Skype::~Skype()
{
    delete client;
}

unsigned Skype::getChatsCount() const
{
    return chats.count();
}

QStringList Skype::getChatsNames() const
{
    return chats.keys();
}

void Skype::addAction(Action *a)
{
    if(a){
        actions.push_back(a);
    }
}

void Skype::updateChats()
{
    chats.clear();
    QAxObject *obj = this->querySubObject("Chats()");
    if(obj != NULL){
        const int count = obj->dynamicCall("Count()").toInt();
        for(int i = 1; i <= count; i++){
            QAxObject *chat = obj->querySubObject("Item(int)", QVariant(i));
            if(chat != NULL){
                const QString friendlyName = chat->dynamicCall("FriendlyName()").toString();
                const QString topic = chat->dynamicCall("Topic()").toString();
                if(topic.trimmed().isEmpty()){
                    if(!friendlyName.isEmpty()){
                        chats[friendlyName]=chat;
                    }
                }else{
                    chats[topic]=chat;
                }
            }
        }
    }
}

void Skype::slotMessageSkype(IDispatch *obj, TChatMessageStatus)
{
    QAxObject *msg= new QAxObject((IUnknown*)obj);
    if(msg){        
        const QString text = msg->dynamicCall("Body()").toString();
        if(text.startsWith('!')){
            if(text == "!plugins"){
                QString info = "Plugins information:\n";
                if(actions.isEmpty()){
                    info += "Plugin list is empty!";
                }else{
                    for (int i = 0 ; i < actions.count(); i++){
                      Action *a = actions[i];
                        info += "[" + a->getName() + "]\n" +
                             "description:" + a->getInfo() + '\n'+
                             "key words:\n" + a->getKeys().join('\n') + '\n';
                    }
                }
                msg->querySubObject("Chat()")->dynamicCall("SendMessage(QString)",info);
            }else{
              for (int i = 0 ; i < actions.count(); i++){
                Action *a = actions[i];
                    a->execute(msg);
                }
            }
        }
    }
    delete msg;
}

void Skype::slotException(int, QString, QString, QString)
{

}

