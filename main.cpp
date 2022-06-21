#include <mainclass.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<QString> QArgv(argc, QString ());
    for(int i=0; i <argc; i++){
        QArgv[i]=argv[i];
    }
    QArgv.pop_front();
    MainClass obj(QArgv);
    return 0;
}
