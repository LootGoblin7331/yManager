#include "searchtask.h"
#include "ui_searchtask.h"

SearchTask::SearchTask(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::SearchTask)
{
    _ui->setupUi(this);
}

SearchTask::SearchTask(std::list<Task> *taskList, QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::SearchTask)
{
    _ui->setupUi(this);

    this->_taskList = taskList;

    setWindowModality(Qt::ApplicationModal);
}
SearchTask::~SearchTask()
{
    delete _ui;
}

void SearchTask::on_pushButton_clicked()
{
    SerchingTask();
}

void SearchTask::SerchingTask()
{
    std::string titleSearching = this->_ui->lineEdit->text().toStdString();
    std::string dateSearching = this->_ui->lineEdit_2->text().toStdString();
    Task *temp;
    std::list<Task> bufferListFirst = std::list<Task>();
    std::list<Task> bufferListSecond = std::list<Task>();


    if(this->_ui->checkBox->isChecked())
        if(!titleSearching.empty())
        {
            for(std::list<Task>::iterator elem = this->_taskList->begin(); elem != this->_taskList->end(); elem++)
            {
                if(elem->GetTitle() == titleSearching)
                {
                    temp = new Task(*elem);

                    bufferListFirst.emplace_back(temp);
                }
            }

            if(this->_ui->checkBox_2->isChecked())
            {
                for(std::list<Task>::iterator elem = bufferListFirst.begin(); elem != bufferListFirst.end(); elem++)
                {
                    if((QString::number(elem->GetDay())+"."+QString::number(elem->GetMonth())+
                         "."+QString::number(elem->GetYear())).toStdString() == dateSearching)
                    {
                        temp = new Task(*elem);

                        bufferListSecond.emplace_back(temp);
                    }
                }

                if(!bufferListSecond.empty())
                {
                    std::list<Task>::iterator it = bufferListSecond.begin();

                    temp = new Task(*it);

                    this->_aboutTask = new AboutTask(temp);

                    this->_aboutTask->setWindowTitle("Подробно о задаче");

                    this->_aboutTask->setWindowModality(Qt::ApplicationModal);

                    this->_aboutTask->show();

                    return;
                }
            }


            if(!bufferListFirst.empty())
            {
                std::list<Task>::iterator it = bufferListFirst.begin();

                temp = new Task(*it);

                this->_aboutTask = new AboutTask(temp);

                this->_aboutTask->setWindowModality(Qt::ApplicationModal);

                this->_aboutTask->show();

                return;
            }
    }

    if(this->_ui->checkBox_2->isChecked())
        if(!dateSearching.empty())
        {
            for(std::list<Task>::iterator elem = this->_taskList->begin(); elem != this->_taskList->end(); elem++)
            {
                if((QString::number(elem->GetDay())+"."+QString::number(elem->GetMonth())+
                     "."+QString::number(elem->GetYear())).toStdString() == dateSearching)
                {
                    temp = new Task(*elem);

                    bufferListFirst.emplace_back(temp);
                }
            }

            if(!bufferListFirst.empty())
            {
                std::list<Task>::iterator it = bufferListFirst.begin();

                temp = new Task(*it);

                this->_aboutTask = new AboutTask(temp);

                this->_aboutTask->setWindowModality(Qt::ApplicationModal);

                this->_aboutTask->show();

                return;
            }
        }
}





