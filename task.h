#ifndef TASK_H
#define TASK_H

#pragma once

#include <iostream>
#include <iomanip>
#include <QDate>

class Task
{
private:

    std::string _title;

    short _day;
    short _month;
    short _year;

    short _priority; // 0 низки, 1 обычн, 2 высок, 3 срочн.

    std::string _description;


public:
    Task();

    Task(std::string title, std::string description, short day, short month, short year, short priority = 1);

    Task(Task *taskForCopy);

    std::string GetDescription();

    unsigned short GetDay();

    unsigned short GetMonth();

    unsigned short GetYear();

    QDate GetDate();

    std::string GetTitle();

    unsigned short GetPriority();

    std::string GetPriorityString();

};


#endif // TASK_H
