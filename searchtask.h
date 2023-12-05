#ifndef SEARCHTASK_H
#define SEARCHTASK_H

#include <QWidget>
#include "task.h"
#include "abouttask.h"

namespace Ui {
class SearchTask;
}

class SearchTask : public QWidget
{
    Q_OBJECT

public:
    explicit SearchTask(QWidget *parent = nullptr);
    explicit SearchTask(std::list<Task> *taskList, QWidget *parent = nullptr);
    ~SearchTask();

private slots:

    void on_pushButton_clicked();

private:
    Ui::SearchTask *_ui;
    std::list<Task> *_taskList;
    AboutTask *_aboutTask;

    void SerchingTask();
};

#endif // SEARCHTASK_H
