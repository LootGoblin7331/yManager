#ifndef CREATETASK_H
#define CREATETASK_H

#include <QWidget>
#include "task.h"

namespace Ui {
class CreateTask;
}

class CreateTask : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTask(QWidget *parent = nullptr);
    ~CreateTask();

    Task SavedTask(); //Инициализирует объект типа Task из полей виджета и возвращает этот объект.

    void InitList(std::list<Task> *taskList); //передача листа по ссылке для взаимодействия с ним.

private slots:
    void on_buttonBox_rejected(); //Виджет кнопка Отмена

    void on_buttonBox_accepted(); //Виджет кнопка Ок

private:
    Ui::CreateTask *_ui;
    std::list<Task> *_taskList;

signals:
    void SignalAccepted();
};

#endif // CREATETASK_H
