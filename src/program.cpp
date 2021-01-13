#include "program.hpp"
#include "commands.hpp"
#include <iostream>
#include <string>
#include <exception>
#include <limits>
#include <vector>

using namespace std;

void initProgram()
{
    splashScreen();
    cout << "* Enter help command to guide you\n" << endl;
    getCommand();
    cout << "* program finished!" << endl;
}

void splashScreen()
{
    cout << "   ------------------------>" << endl;
    cout << "#--|      smart tasks      |--#" << endl;
    cout << "|  <------------------------  |" << endl;
    cout << "|  manager of your time and   |" << endl;
    cout << "|  plans. dont worry about    |" << endl;
    cout << "|  losing your opportunity    |" << endl;
    cout << "|  anymore!                   |" << endl;
    cout << "#-----------------------------#\n" << endl;
}


void getCommand()
{
    bool programStatus = true;      //program power off/on
    vector <Task> tasks;            //tasks is a vector object that saves all user tasks
    Commands commands;              //commands object deals with user inputed commands

    do
    {   
        //get command from user
        cout << "> ";
        string inputedCommand;
        getline(cin, inputedCommand);

        //detect user inputed commands

        //--------------- exit ---------------
        if(inputedCommand == "exit")
        {
            programStatus = false;      //breaks the do-while loop
            continue;                   //avoid flushing cin buffer
        }
        //--------------- add ---------------
        else if(inputedCommand == "add")
        {
            try
            {
                commands.addTask(tasks);
            }
            catch(invalid_argument & mess)
            {
                cerr << mess.what() << endl;
                cerr << "* Task did not add!" << endl;
            }  
        }
        //--------------- delete ---------------
        else if(inputedCommand == "delete")
        {
            try
            {
                commands.deleteTask(tasks);
            }
            catch(invalid_argument & mess)
            {
                cerr << mess.what() << endl;
            }  
        }
        //--------------- complete ---------------
        else if(inputedCommand == "complete")
        {
            try
            { 
                commands.CompleteTask(tasks);
            }
            catch(invalid_argument & mess)
            {
                cerr << mess.what() << endl;
            }
        }
        //--------------- edit ---------------
        else if(inputedCommand == "edit")
        {
            try
            { 
            commands.editTask(tasks);
            }
            catch(invalid_argument & mess)
            {
                cerr << mess.what() << endl;
                continue;       //avoid flushing cin buffer
            } 
        }
        //--------------- list-todo ---------------
        else if(inputedCommand == "list-todo")
        {
            commands.listTodo(tasks);
            continue;       //avoid flushing cin buffer
        }
        //--------------- list-complete ---------------
        else if(inputedCommand == "list-complete")
        {
            commands.listComplete(tasks);
            continue;       //avoid flushing cin buffer

        }
        //--------------- help ---------------
        else if(inputedCommand == "help")
        {
            commands.help();
        }
        //--------------- lother situations ---------------
        else
        {
            //if user dont input any command, it will not print any character,
            //else if inpted command is EOF(ctrl+d in linux/mac os), it will break,
            //otherwise inputed command is an undefined command!
            if(!inputedCommand.empty()) 
            {
                cout << "* undefined command!" << endl;
            }
            else if(cin.eof())
            {
                programStatus = false;
                cout << endl;
            }

            continue;   //avoid flushing cin buffer
        }

       // clearBuff();
    }
    while (programStatus == true);
}


void clearBuff(void)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
}