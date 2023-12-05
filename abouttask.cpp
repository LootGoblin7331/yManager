#include "abouttask.h"
#include "ui_abouttask.h"

AboutTask::AboutTask(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::AboutTask)
{
    _ui->setupUi(this);

    _ui->calendarWidget_2->setSelectionMode(QCalendarWidget::NoSelection);
}

AboutTask::AboutTask(class Task *task, QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::AboutTask)
{
    _ui->setupUi(this);

    this->_task = task;

    SetInfo();
}

AboutTask::~AboutTask()
{
    delete _ui;
}

void AboutTask::SetInfo()
{
    _ui->lineEdit_3->setText(QString::fromStdString(this->_task->GetTitle()));
    _ui->lineEdit_4->setText(QString::fromStdString(this->_task->GetDescription()));
    _ui->spinBox_2->setValue(this->_task->GetPriority());
    _ui->label->setText(QString::fromStdString(this->_task->GetPriorityString()));
    QDate date(this->_task->GetYear(), this->_task->GetMonth(), this->_task->GetDay());
    _ui->calendarWidget_2->setSelectedDate(date);

    _ui->lineEdit_3->setReadOnly(true);
    _ui->lineEdit_4->setReadOnly(true);
    _ui->spinBox_2->setReadOnly(true);
    _ui->calendarWidget_2->setSelectionMode(QCalendarWidget::NoSelection);
    //_ui->calendarWidget_2->setNavigationBarVisible(false);
    //_ui->calendarWidget_2->setEnabled(false);
}

void AboutTask::on_pushButton_clicked()
{
    close();
}

