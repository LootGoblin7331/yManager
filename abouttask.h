#ifndef ABOUTTASK_H
#define ABOUTTASK_H

#include <QWidget>
#include <QDate>
#include "task.h"

namespace Ui {
class AboutTask;
}

class AboutTask : public QWidget
{
    Q_OBJECT

public:
    explicit AboutTask(QWidget *parent = nullptr);
    explicit AboutTask(class Task *task, QWidget *parent = nullptr);

    ~AboutTask();

    void SetInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AboutTask *_ui;
    Task *_task;
    std::list<Task> *_taskList;
};

#endif // ABOUTTASK_H
