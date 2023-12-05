#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _tl = new QList<QString>();

    this->_db = new DbConnect;

    this->_taskList = std::list<Task>();

    this->_db->GetDatabaseItems(this->_taskList);

    UpdateListWidget();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->_createTaskWindow = new CreateTask();

    this->_createTaskWindow->setWindowTitle("Создать задачу");

    this->_createTaskWindow->InitList(&_taskList);

    connect(this->_createTaskWindow, &CreateTask::SignalAccepted, this, &MainWindow::slotAsseptedCreateTask);

    this->_createTaskWindow->show();
}

void MainWindow::UpdateListWidget()
{
    delete this->_tl;
    this->_tl = new QList<QString>();

    this->_ui->listWidget->clear();

    for(auto l : this->_taskList)
    {
        _tl->append(QString::fromStdString(l.GetTitle()) +
                    " | приоритет: "+
                    QString::fromStdString(l.GetPriorityString())+" | "+
                    QString::number(l.GetDate().day())+"."+
                    QString::number(l.GetDate().month())+"."+
                    QString::number(l.GetDate().year()));
    }

    int count = 0;
    for(auto l : *_tl)
    {
        this->_ui->listWidget->addItem(l);
        this->_ui->listWidget->item(count)->setTextAlignment(Qt::AlignRight);
        count++;
    }
}

void MainWindow::slotAsseptedCreateTask()
{
    this->_db->UpdateTable(this->_taskList);

    UpdateListWidget();
}

void MainWindow::ChoiceItemInListWidget()
{
    if(!this->_taskList.empty() && this->_ui->listWidget->currentRow() >= 0)
    {
        int indexOfElement = this->_ui->listWidget->currentRow();

        std::list<Task>::iterator it = this->_taskList.begin();

        std::advance(it, indexOfElement);

        Task *temp = new Task(it->GetTitle(), it->GetDescription(),
                              it->GetDay(), it->GetMonth(), it->GetYear() ,it->GetPriority());

        this->_aboutTask = new AboutTask(temp);

        this->_aboutTask->setWindowTitle("Подробно о задаче");

        this->_aboutTask->show();
    }
    else
    {
        this->_ui->statusbar->showMessage("Невозможно получить подробные сведенья: задача не выбрана или задачи отсутствуют.");
    }
}

void MainWindow::on_pushButton_clicked()
{
    ChoiceItemInListWidget();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(!this->_taskList.empty())
    {
        int indexOfElement = this->_ui->listWidget->row(item);

        std::list<Task>::iterator it = this->_taskList.begin();

        std::advance(it, indexOfElement);

        Task *temp = new Task(it->GetTitle(), it->GetDescription(),
                              it->GetDay(), it->GetMonth(), it->GetYear() ,it->GetPriority());

        this->_aboutTask = new AboutTask(temp);

        this->_aboutTask->setWindowTitle("Подробно о задаче");

        this->_aboutTask->show();
    }
    else
    {
        this->_ui->statusbar->showMessage("Невозможно получить подробные сведенья: задача не выбрана или задачи отсутствуют.");
    }
}

void MainWindow::DeleteTask()
{
    if(this->_ui->listWidget->currentRow() != -1 && !this->_taskList.empty())
    {
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Подтверждение удаления", "Вы уверенны что хотите удалить эту задачу?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            int indexOfElement = this->_ui->listWidget->currentRow();

            std::list<Task>::iterator it = this->_taskList.begin();

            std::advance(it, indexOfElement);

            this->_taskList.erase(it);

            this->_ui->statusbar->showMessage("Задача удалена из списка.");
        }
        else
        {
            this->_ui->statusbar->showMessage("Удаление отменено.");
        }
    }
    else
    {
        this->_ui->statusbar->showMessage("Удаление невозможно: задача не выбрана или возник непредвиденный конфликт.");
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    DeleteTask();

    this->_db->UpdateTable(this->_taskList);

    UpdateListWidget();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->_searchTask = new SearchTask(&_taskList);

    this->_searchTask->setWindowTitle("Поиск задачи");

    this->_searchTask->show();
}

