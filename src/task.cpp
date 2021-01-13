#include "task.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Task::Task()  //defualt constructor for temporary objects
{
    setID();
}

Task::Task(const Task & copyTask)      //copy constructor
{
    setName(copyTask.getName());
    setPriority(copyTask.getPriority());
    setFavorite(copyTask.getFavorite());
    this->ID_ = copyTask.getID();
    setComplete(copyTask.getComplete());
}


void Task::setName(string name)
{
    if(name.empty())
    {
        throw invalid_argument("* You must set a task name!");
    }

    this->name_ = name;
}


void Task::setPriority(unsigned int priority)
{
    if(priority >= 1 && priority <= 5)
    {
        this->priority_ = priority;
    }
    else
    {
        throw invalid_argument("* Priority must be in [1, 5] period!");
    } 
}


void Task::setFavorite(bool favorite)
{
    this->favorite_ = favorite;
}


void Task::setID(void)
{
    srand(time(NULL));
    this->ID_ = rand()%10000;
}


void Task::setComplete(bool boolValue)
{
    this->isComplete_ = boolValue;
}


string Task::getName(void) const
{
    return name_;
}


size_t Task::getNameSize(void) const
{
    return name_.size();
}


unsigned int Task::getPriority(void) const
{
    return priority_;
}


bool Task::getFavorite(void) const
{
    return favorite_;
}


unsigned int Task::getID(void) const
{
    return ID_;
}


bool Task::getComplete(void) const
{
    return isComplete_;
}