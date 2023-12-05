#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QString>
#include <QtSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtGui>
#include <string.h>

#include "task.h"

class QSqlDatabase;

class DbConnect
{
public:
    DbConnect();
    ~DbConnect();

    void CreateTable();

    int InsertToTable(QString NameTask, QString DescriptionTask,
               QString Day, QString Month, QString Year, QString Priority); //метод вставки

    void UpdateTable(std::list<Task> &taskList);
        //еще много разных методов
    void GetDatabaseItems(std::list<Task> &taskList);

private:

    const char *_dbName = "my_sqlite.db";

    QSqlDatabase _db; //наша БД
};

#endif // DBCONNECT_H
