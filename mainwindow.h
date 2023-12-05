#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMessageBox>
#include "task.h"
#include "createtask.h"
#include "abouttask.h"
#include "dbconnect.h"
#include "searchtask.h"
#include <iomanip>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked(); // button CreatedTask

    void on_pushButton_clicked(); //button AboutTask

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item); //doubleclick choice AboutTask

    void on_pushButton_5_clicked(); // button Delete

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *_ui;
    std::list<Task> _taskList;
    QList<QString> *_tl;
    CreateTask *_createTaskWindow;
    AboutTask *_aboutTask;
    DbConnect *_db;
    SearchTask *_searchTask;

    void UpdateListWidget(); //method of update widget whith title list
    void ChoiceItemInListWidget(); //method of selecting a line in the widget function
    void DeleteTask();  //method of deleting task

public slots:
    void slotAsseptedCreateTask(); // catches the click of the Ok button in CreateTask
};
#endif // MAINWINDOW_H
