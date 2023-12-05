#include "createtask.h"
#include "ui_createtask.h"

CreateTask::CreateTask(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::CreateTask)
{
    _ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);
}

CreateTask::~CreateTask()
{
    delete _ui;
}

void CreateTask::on_buttonBox_rejected()
{
    close();
}

void CreateTask::on_buttonBox_accepted()
{
    if(!this->_ui->lineEdit->displayText().isEmpty())
    {
        this->_taskList->push_back(SavedTask());

        emit this->SignalAccepted();

        close();
    }
}

Task CreateTask::SavedTask()
{
    std::string title = _ui->lineEdit->text().toStdString();
    std::string description = _ui->lineEdit_2->text().toStdString();
    unsigned short day = _ui->calendarWidget->selectedDate().day();
    unsigned short month = _ui->calendarWidget->selectedDate().month();
    unsigned short year = _ui->calendarWidget->selectedDate().year();
    unsigned short priority = _ui->spinBox->value();

    if(description.empty())
        description = "Описание отсутствует";

    Task *savingTask = new Task(title, description, day, month, year, priority);

    return *savingTask;
}

void CreateTask::InitList(std::list<Task> *taskList)
{
    this->_taskList = taskList;
}





