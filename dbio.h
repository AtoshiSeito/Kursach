#ifndef DBIO_H
#define DBIO_H
#include <QtSql>
#include <QDebug>

class DBIO
{
private:
    QSqlDatabase DataBase;
    void UpdateManCount(QString id);
public:
    DBIO();
    void AddDev(QVector<QString> QArgv);
    void EditDev(QVector<QString> QArgv);
    void DeleteDev(QVector<QString> QArgv);

    void AddCad(QVector<QString> QArgv);
    void EditCad(QVector<QString> QArgv);
    void DeleteCad(QVector<QString> QArgv);

    void AddOf(QVector<QString> QArgv);
    void EditOf(QVector<QString> QArgv);
    void DeleteOf(QVector<QString> QArgv);
};

#endif // DBIO_H
