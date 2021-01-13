#ifndef COMMANDS_IG
#define COMMANDS_IG

#include "task.hpp"
#include "program.hpp"
#include <vector>

class Commands
{
    public:
        //CRUD tasks vector
        void addTask(std::vector <Task> &);
        void deleteTask(std::vector <Task> &);
        void CompleteTask(std::vector <Task> &);
        void editTask(std::vector <Task> &);
        void listTodo(std::vector <Task> &);
        void listComplete(std::vector <Task> &);
        //show program commands that user can input them
        void help();
    private:
        //returns vector index by its ID
        int findTaskByID(std::vector <Task> &, const unsigned int);  
        //for yes/no questions
        bool getYesNoCommand();
        //get maximum name size in all Task objects
        size_t getMaxNameSize(std::vector <Task> &);       
};


#endif