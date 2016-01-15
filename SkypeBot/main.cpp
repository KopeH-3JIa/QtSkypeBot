#include <QApplication>
#include "skype.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QLibrary>

void findPlugins(Skype &skype);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("NoobyJoe");
    Skype skype;
    findPlugins(skype);
    skype.updateChats();
    return a.exec();
}




void findPlugins(Skype &skype)
{
  qDebug() << "Load plugins!";
    const QFileInfo file(qApp->arguments()[0]);
    const QString path(file.absolutePath() + "/plugins");
    QDir dir(path);
    if(dir.exists()){
        const QStringList files = dir.entryList(QDir::Files);
        for(int i = 0; i < files.count(); i++){
          const QString &lib = files[i];
            if(QLibrary::isLibrary(lib)){
                   qDebug() << "Load " << path + "/" + lib;
                   QLibrary plugin(path + "/" + lib);
                   plugin.load();
                   typedef Action* (*DllActionCreate)(void);
                   DllActionCreate create = (DllActionCreate)plugin.resolve("createAction");
                   if(create){
                      qDebug() << "Done " << lib;
                      skype.addAction(create());
                   }else{
                      qDebug() << "None " << lib << plugin.errorString();
                   }
            }
        }
    }
}
