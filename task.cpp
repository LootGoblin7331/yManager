#include "task.h"

Task::Task()
{
    this->_title = "Добавьте заголовок";
    this->_description = "Добавьте описание...";

    this->_day = 0;
    this->_month = 0;
    this->_year = 0;

    this->_priority = 1;
}

Task::Task(std::string title, std::string description, short day, short month, short year, short priority)
{
    this->_title = title;
    this->_description = description;


    if (year >= 2023)
        this->_year = year;
    else
        this->_year = 2023;

    if (month > 0 && day <= 12)
        this->_month = month;
    else if (month <= 0)
        this->_month = 1;
    else
        this->_month = 12;

    if (day <= QDate(this->_year, this->_month, 15).daysInMonth() && day > 0)
        this->_day = day;
    else if(day <= 0)
        this->_day = 1;
    else
        this->_day = QDate(this->_year, this->_month, 15).daysInMonth();

    if (priority <= 2 && priority >= 0)
        this->_priority = priority;
    else if(priority > 2)
        this->_priority = 2;
    else
        this->_priority = 0;
}

Task::Task(Task *taskForCopy)
{

    this->_title = taskForCopy->GetTitle();
    this->_description = taskForCopy->GetDescription();
    this->_day = taskForCopy->GetDay();
    this->_month = taskForCopy->GetMonth();
    this->_year = taskForCopy->GetYear();
    this->_priority = taskForCopy->GetPriority();
}

std::string Task::GetTitle()
{
    return this->_title;
}

unsigned short Task::GetPriority()
{
    return this->_priority;
}

std::string Task::GetPriorityString()
{
    switch (GetPriority())
    {
    case 0:
        return "низкий";
        break;
    case 1:
        return "обычный";
        break;
    case 2:
        return "срочный!";
        break;
    default:
        return "срочный!";
    }
}

unsigned short Task::GetDay()
{
    return this->_day;
}

unsigned short Task::GetMonth()
{
    return this->_month;
}

unsigned short Task::GetYear()
{
    return this->_year;
}

QDate Task::GetDate()
{
    QDate *dateTask = new QDate(this->_year, this->_month, this->_day);

    return *dateTask;
}

std::string Task::GetDescription()
{
    return _description;
}

