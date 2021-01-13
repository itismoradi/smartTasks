#ifndef TASK_IG
#define TASK_IG

#include <string>

class Task
{
    public:
        Task();                 //defualt constructor
        Task(const Task&);      //copy constructor
        void setName(std::string);
        void setPriority(unsigned int);
        void setFavorite(bool);
        void setComplete(bool);

        std::string getName(void) const;
        size_t getNameSize(void) const;
        unsigned int getPriority(void) const;
        bool getFavorite(void) const;
        unsigned int getID(void) const;
        bool getComplete(void) const;
    private:
        void setID(void);       //random assign an ID to task object

        std::string name_;
        unsigned int priority_;
        bool favorite_ = false;
        unsigned int ID_;
        bool isComplete_ = false;
};

#endif