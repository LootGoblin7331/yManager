#include "dbconnect.h"

#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql>

DbConnect::DbConnect()
{   
    //строка соединения
    QString connection = QString(QSqlDatabase::defaultConnection);
    //это нужно, чтобы не возникало ошибки о повторном соединении, так НАДА
    if(QSqlDatabase::contains(connection))
    {
        this->_db = QSqlDatabase::addDatabase(connection);
    }
    {
        this->_db = QSqlDatabase::addDatabase("QSQLITE", connection);
        //вписываем имя БД
        this->_db.setDatabaseName(this->_dbName);
        //открываем соединение
        this->_db.open();
    }
}

void DbConnect::CreateTable()
{
    QSqlQuery query;

    if(!query.exec("CREATE TABLE TaskList "
                  "(NameTask VARCHAR(40),"
                  " DescriptionTask VARCHAR(500),"
                  " Day INT,"
                  " Month INT,"
                  " Year INT,"
                  " Priority INT)"))
    {
        qDebug() << query.lastError().text();
    }
}

int DbConnect::InsertToTable(QString NameTask, QString DescriptionTask,
                      QString Day, QString Month, QString Year, QString Priority)
{
    QSqlQuery query;

    query.prepare("INSERT INTO TaskList "
                  "(NameTask, DescriptionTask, "
                  "Day, Month, Year, Priority) "
                  "VALUES (?, ?, ?, ?, ?, ?)");

//    addBindValue решает проблему экранирования, поэтому добавлять значения надо именно этой функцией
    query.addBindValue(NameTask);
    query.addBindValue(DescriptionTask);
    query.addBindValue(Day);
    query.addBindValue(Month);
    query.addBindValue(Year);
    query.addBindValue(Priority);

    if (!query.exec()) {
        QMessageBox::warning(0,"Error", query.lastQuery());
        return -1;
    }

    int rer = query.lastInsertId().toInt();

    return rer;
}

void DbConnect::UpdateTable(std::list<Task> &taskList)
{
    QSqlQuery query;

    query.prepare("DROP TABLE TaskList");
    query.exec();

    CreateTable();

    for(std::list<Task>::iterator it = taskList.begin(); it != taskList.end(); it++)
        InsertToTable(QString::fromStdString(it->GetTitle()), QString::fromStdString(it->GetDescription()),
                  QString::number(it->GetDay()), QString::number(it->GetMonth()),
                  QString::number(it->GetYear()), QString::number(it->GetPriority()));
}

void DbConnect::GetDatabaseItems(std::list<Task> &taskList)
{
    QSqlQuery q = QSqlQuery(this->_db);

    q.prepare("SELECT * from TaskList");
    q.exec();

    std::string name, description;
    int day = 0, month = 0, year = 0, priority = 0;

    while (q.next()){
        name = q.value(0).toString().toStdString();
        description = q.value(1).toString().toStdString();
        day = q.value(2).toInt();
        month = q.value(3).toInt();
        year = q.value(4).toInt();
        priority = q.value(5).toInt();

        Task *newTask = new Task(name, description, day, month, year, priority);

        taskList.push_back(*newTask);
    }
}

DbConnect::~DbConnect()
{
    this->_db.close();
}
