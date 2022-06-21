#include "dbio.h"

DBIO::DBIO()
{
    DataBase = QSqlDatabase::addDatabase("QSQLITE");
    DataBase.setDatabaseName("C:/Qt/Projects/Kursach/MainDB.db");
    if(!DataBase.open()){
        //Не найдена база!!!
    }
    QSqlQuery DBQuery;
    DBQuery.exec("CREATE TABLE IF NOT EXISTS division (id INTEGER PRIMARY KEY NOT NULL UNIQUE, manscounter INTEGER, idOf INTEGER)");
    DBQuery.exec("CREATE TABLE IF NOT EXISTS cadet (id INTEGER PRIMARY KEY NOT NULL UNIQUE, secondname STRING NOT NULL, firstName STRING NOT NULL, thirdName STRING NOT NULL, idDiv INTEGER NOT NULL, idOf INTEGER)");
    DBQuery.exec("CREATE TABLE IF NOT EXISTS oficer (id INTEGER PRIMARY KEY NOT NULL UNIQUE, secondname STRING NOT NULL, firstName STRING NOT NULL, thirdName STRING NOT NULL, idDiv INTEGER)");
}

void DBIO::AddDev(QVector<QString> QArgv)
{
    QSqlQuery DBQuery;
    if(QArgv.size()<1){
        return;
    }
    if(QArgv.size()==1){
        DBQuery.exec(QString("INSERT INTO division(id) VALUES (%1)").arg(QArgv[0]));
    } else {
        DBQuery.exec(QString("INSERT INTO division(id, idOF) VALUES (%1, %2)").arg(QArgv[0]).arg(QArgv[1]));
    }
    UpdateManCount(QArgv[0]);
}

void DBIO::EditDev(QVector<QString> QArgv)
{
    QSqlQuery DBQuery;
    if(QArgv.size()!=0){
        QString lastId = QArgv[0];
        QArgv.pop_front();
        while(QArgv.size())
            if(QArgv.size()>1){
                if(QArgv[0]=="id"){
                    QArgv.pop_front();
                    if(DBQuery.exec(QString("UPDATE division SET id = %1 WHERE id = %2").arg(QArgv[0]).arg(lastId))){
                        DBQuery.exec(QString("UPDATE cadet SET idDev = %1 WHERE idDiv = %2").arg(QArgv[0]).arg(lastId));
                        DBQuery.exec(QString("UPDATE oficer SET idDev = %1 WHERE idDiv = %2").arg(QArgv[0]).arg(lastId));
                    }
                } else if(QArgv[0]=="idOf"){
                    QArgv.pop_front();
                    DBQuery.exec(QString("UPDATE division SET idOf = %1 WHERE id = %2").arg(QArgv[0]).arg(lastId));
                    DBQuery.exec(QString("UPDATE oficer SET idDiv = NULL WHERE idDiv = %1").arg(lastId));
                    DBQuery.exec(QString("UPDATE oficer SET idDiv = %1 WHERE idDiv = %2").arg(QArgv[0]).arg(lastId));
                    DBQuery.exec(QString("UPDATE cadet SET idOf = %1 WHERE idDiv = %2").arg(QArgv[0]).arg(lastId));
                }
                QArgv.pop_front();
            }
    }
}

void DBIO::DeleteDev(QVector<QString> QArgv)
{
    if(QArgv.size()){
        QSqlQuery DBQuery;
        DBQuery.exec(QString("DELETE FROM division WHERE id = %1").arg(QArgv[0]));
        DBQuery.exec(QString("DELETE FROM cadet WHERE idDiv = %1").arg(QArgv[0]));
        DBQuery.exec(QString("UPDATE oficer SET idDiv = NULL WHERE idDiv = %1").arg(QArgv[0]));
    }
}

void DBIO::AddCad(QVector<QString> QArgv)
{
    if(QArgv.size()==5){
        QSqlQuery DBQuery;
        DBQuery.exec(QString("SELECT * FROM division WHERE id = %1").arg(QArgv[4]));
        DBQuery.next();
        QString idOf=DBQuery.value("idOf").toString();
        DBQuery.next();
        DBQuery.exec(QString("INSERT INTO cadet(id, secondName, firstName, thirdName, idDiv, idOf) VALUES (%1, %2, %3, %4, %5, %6)").arg(QArgv[0]).arg("'"+QArgv[1]+"'").arg("'"+QArgv[2]+"'").arg("'"+QArgv[3]+"'").arg("'"+QArgv[4]+"'").arg(idOf));
        UpdateManCount(QArgv[4]);
        qDebug()<<DBQuery.lastError().text();
    }
}

void DBIO::EditCad(QVector<QString> QArgv)
{
    QSqlQuery DBQuery;
    if(QArgv.size()!=0){
        QString lastId = QArgv[0];
        QArgv.pop_front();
        while(QArgv.size())
            if(QArgv.size()>1){
                if(QArgv[0]=="id"){
                    QArgv.pop_front();
                    if(DBQuery.exec(QString("UPDATE cadet SET id = %1 WHERE id = %2").arg(QArgv[0]).arg(lastId))){
                    }
                } else if(QArgv[0]=="idDiv"){
                    QArgv.pop_front();
                    DBQuery.exec(QString("UPDATE cadet SET idDiv = %1 WHERE id = %2").arg(QArgv[0]).arg(lastId));
                    DBQuery.exec(QString("SELECT * FROM division WHERE id = %1").arg(QArgv[0]));
                    DBQuery.next();
                    QString idOf=DBQuery.value("idOf").toString();
                    DBQuery.exec(QString("UPDATE cadet SET idOf = %1 WHERE idDiv = %2").arg(QArgv[0]).arg(lastId));
                }
                QArgv.pop_front();
            }
    }
}

void DBIO::UpdateManCount(QString id)
{
    QSqlQuery DBQuery;
    int counter = 0;
    DBQuery.exec(QString("SELECT * FROM cadet WHERE idDiv = %1").arg(id));
    while(DBQuery.next()){
            counter++;
    }
    DBQuery.exec(QString("UPDATE division SET manscounter = %1 WHERE id = %2").arg(counter).arg(id));
}
