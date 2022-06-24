#include "mainclass.h"

MainClass::MainClass(QVector<QString> QArgv)
{
    if(QArgv.size()){
        DBIO obj;
        if(QArgv[0]=="division"){
            QArgv.pop_front();
            if(QArgv.size()){
                if(QArgv[0]=="add"){
                    QArgv.pop_front();
                    obj.AddDev(QArgv);
                } else if(QArgv[0]=="edit"){
                    QArgv.pop_front();
                    obj.EditDev(QArgv);
                } else if(QArgv[0]=="delete"){
                    QArgv.pop_front();
                    obj.DeleteDev(QArgv);
                }
            }
        } else if(QArgv[0]=="cadet"){
            QArgv.pop_front();
            if(QArgv.size()){
                if(QArgv[0]=="add"){
                    QArgv.pop_front();
                    obj.AddCad(QArgv);
                } else if(QArgv[0]=="edit"){
                    QArgv.pop_front();
                    obj.EditCad(QArgv);
                } else if(QArgv[0]=="delete"){
                    QArgv.pop_front();
                    obj.DeleteCad(QArgv);
                }
            }
        } else if(QArgv[0]=="oficer"){
            QArgv.pop_front();
            if(QArgv.size()){
                if(QArgv[0]=="add"){
                    QArgv.pop_front();
                    obj.AddOf(QArgv);
                }
            }
        }
    }

}
