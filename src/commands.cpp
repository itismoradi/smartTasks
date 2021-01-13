#include "commands.hpp"
#include "task.hpp"
#include <iostream>
#include <iomanip>
#include <exception>

using namespace std;

void Commands::addTask(vector <Task> & taskList)
{
    Task inputedTask;       //a temporary object for taskList copy constructor
    string inputedTaskName;
    unsigned int inputedTaskPriority;
    bool inputedTaskFavorite;

    cout << "> " << "Task Name : ";
    getline(cin, inputedTaskName);

    cout << "> " << "Priority 1(most) to " << 5 << "(least) : ";
    cin >> inputedTaskPriority;
    cin.clear();
    
    cout << "> " << "Favorite (y/n) : ";
    inputedTaskFavorite = getYesNoCommand();

    inputedTask.setName(inputedTaskName);
    inputedTask.setPriority(inputedTaskPriority);
    inputedTask.setFavorite(inputedTaskFavorite);

    taskList.push_back(inputedTask);

    cout << "* Your task has been successfully added to the list." << endl;
    cout << "  Task Information :"                                          << endl;
    cout << "  "        << taskList.back().getName()                            << " | "; 
    cout << "Priority(" << taskList.back().getPriority()              << ")"    << " | ";
    cout << "Favorite(" << boolalpha << taskList.back().getFavorite() << ")"    << " | ";
    cout << "ID("       << setw(4)  << setfill('0') << taskList.back().getID()  << ")" << endl;
} 


void Commands::deleteTask(vector <Task> & taskList)
{
    unsigned int taskID;
    unsigned int taskPosition;      //to save the findTaskByID function retern value

    cout << "> Enter Task ID : ";
    cin >> taskID;

    taskPosition = findTaskByID(taskList, taskID);
    
    if(taskPosition == -1)
    {
        throw invalid_argument("> Not Found!");
    }
    else
    {
        cout << "> Found! " << taskList.at(taskPosition).getName() << endl;
        cout << "delete (y/n) : ";
        
        if(getYesNoCommand())
        {
            cout << "* Task " << "\"" << taskList.at(taskPosition).getName() << "\"" << " Deleted!" << endl;
            taskList.erase(taskList.begin() + taskPosition);
        }
        else
        {
            cout << "* Task " << "\"" << taskList.at(taskPosition).getName() << "\"" << " Not Deleted!" << endl;
            return;
        }
    } 
}


void Commands::CompleteTask(vector <Task> & taskList)
{
    unsigned int inputedID;
    cout << "Enter Task ID : ";
    cin >> inputedID;
    unsigned int taskPosition = findTaskByID(taskList, inputedID);
    if(taskPosition != -1)
    {
        cout << "> Found! " <<  taskList[taskPosition].getName() << endl;

        if(taskList[taskPosition].getComplete())
        {
            cout << "* The task has already been completed!" << endl;
            return;     //avoid doing another statement
        }

        cout << "complete (y/n) : ";

        if(getYesNoCommand())
        {
            taskList[taskPosition].setComplete(true);
            cout << "> Task " << "\"" << taskList.at(taskPosition).getName() << "\" , " << "completed." << endl;
        }
        else
        {
            cout << "* Task" << taskList.at(taskPosition).getName() << "not completed!" << endl;
        }
    }
    else
    {
        throw invalid_argument("> Not Found!");
    }
    
}


void Commands::editTask(vector <Task> & taskList)
{
    unsigned int inputedID;
    cout << "Enter Task ID : ";
    cin >> inputedID;
    unsigned int taskPosition = findTaskByID(taskList, inputedID);

    if(taskPosition == -1)
    {
        throw invalid_argument("* Not Found!");
    }
    
    cout << "> Found! " << taskList.at(taskPosition).getName() << endl;
    clearBuff();
    string inputedLine;
    getline(cin, inputedLine);

    if(inputedLine.size() == 0)
    {   
        throw invalid_argument("* Empty argument!");
    }

    //-------------- edit function string process --------------

    size_t stringSize = inputedLine.size();
    bool lastProcessInLoop = false;     //if - (dash) is the last edit statement, it will be true

    if(inputedLine.find("-", 1) == string::npos)    //only one - (dash) is there in inputedLine
    {
        lastProcessInLoop = true;
    }

    for(size_t i=0; i<stringSize; i++) 
    {   

        size_t j;   //j is next - (dash) sign index in inputedLine string

        if(!lastProcessInLoop)      //there is a - (dash) after this process
        {
            if(inputedLine.at(i) == '-' && inputedLine.at(i+2) == ' ')
            {
                //find next - (dash) sign
                j = inputedLine.find("-n ", i+3);    

                if(j = string::npos)    //not found another - (dash)
                {
                    lastProcessInLoop = true;
                } 
                else if(j == i+3)    //user did not input any argument after -n or -f or -p
                {
                    throw invalid_argument("* Bad argument!");
                }
            }     
        }
        else    //if it is in last process
        {
            j = *(inputedLine.end()) + 1;
        }
                   


        //detect after - (dash) is there n or f or p or q or bad argument    

        if(inputedLine[i+1] == 'n')
        {
            unsigned int nameSize;
            nameSize = (j-1) - (i+2);
            string inputedName;
            inputedName = inputedLine.substr(i+3, nameSize);
            taskList.at(taskPosition).setName(inputedName);
            cout << "* Task name set \"" << taskList.at(taskPosition).getName() << "\"" << endl;
        }
        else if(inputedLine[i+1] == 'f')
        {
             if(inputedLine[i+3] == 'y')
             {
                taskList.at(taskPosition).setFavorite(true);
                cout << "* Task favorite set " << boolalpha << taskList.at(taskPosition).getFavorite() << endl;
             }
             else if(inputedLine[i+3] == 'n')
             {
                taskList.at(taskPosition).setFavorite(false);
                cout << "* Task favorite set " << boolalpha << taskList.at(taskPosition).getFavorite() << endl;
             }
             else
             {
                 throw invalid_argument("* Bad argument!"); 
             }
             
        }
        else if(inputedLine[i+1] == 'p')
        {
            string inputedPriority;
            inputedPriority = inputedPriority.at(i+3);
            taskList.at(taskPosition).setPriority(stoi(inputedPriority));
            cout << "* Task priority set " << taskList.at(taskPosition).getName() << endl;
        }
        else if(inputedLine[i+1] == 'q')
        {
            cout << "* quit from editing!" << endl;
            return;
        }
        else
        {
            throw invalid_argument("* Bad argument!"); 
        }

    }
    //i will be j. j is next - (dash) sign in inputedLine
}


void Commands::listTodo(vector <Task> & taskList)
{
    cout << setfill(' ');
    size_t MaximumNameChar = getMaxNameSize(taskList); 

    cout << setw(MaximumNameChar + 2) << left << "Task";
    cout << setw(3)  << left << " P";
    cout << setw(3)  << left << " F";
    cout << setw(4)  << left << " ID" << endl;

    for(size_t i=0; i< (MaximumNameChar + 1 + 3 + 3 + 4 + 2); i++)  // MaximumNameChar plus numbers for more beauty
    {
        cout << "_";
    }

    cout << endl;

    for(Task & item : taskList)
    {
            cout << "-";
            cout << setw(MaximumNameChar + 2) << left << item.getName();
            cout << setw(3)  << left << item.getPriority();
            if(item.getComplete())
            {
                cout << setw(3)  << left << "y";
            }
            else
            {
                cout << setw(3)  << left << "n";
            }
            cout << setw(4)  << left << item.getID();
            cout << endl;
    }
}


void Commands::listComplete(vector <Task> & taskList)
{
    cout << setfill(' ');
    size_t MaximumNameChar = getMaxNameSize(taskList); 

    cout << setw(MaximumNameChar + 2) << left << "Task";    // MaximumNameChar + 2 for more beauty
    cout << setw(4)  << left << " ID" << endl;


    for(size_t i=0; i< (MaximumNameChar + 4 + 2); i++)
    {
        cout << "_";
    }

    cout << endl;

    for(Task & item : taskList)
    {
        if(item.getComplete())
        {
            cout << "-";
            cout << setw(MaximumNameChar + 2) << left << item.getName();
            cout << setw(4)  << left << item.getID();
            cout << endl;
        }
    }
}


void Commands::help()
{
    cout << "--------- help ---------" << endl;
    cout << "program commands:" << endl;
    cout << "\t> add" << endl;
    cout << "\t> delete" << endl;
    cout << "\t> complete" << endl;
    cout << "\t> edit" << endl;
    cout << "\t> list-todo" << endl;
    cout << "\t> list-complete" << endl;
    cout << "\t> help" << endl;
    cout << "\t> exit" << endl;
}


int Commands::findTaskByID( std::vector <Task> & tasklist,const unsigned int taskID)
{
    int index = 0;  

    for(Task & item : tasklist)
    {
        if(taskID == item.getID())
        {
            return index;    //index of intended class in vector <Task>
        }

        index++;
    }

    //not found ID
    return -1;
}


bool Commands::getYesNoCommand()
{
    clearBuff();
    
    char ch;

    cin.get(ch);

    if(ch == 'y')
    {
        return true;
    }
    else if(ch == 'n')
    {
        return false;
    }
    else
    {
        throw invalid_argument("* bad character for yes/no question!");
    }
}


size_t Commands::getMaxNameSize(std::vector <Task> & taskList)
{
    size_t MaxSize = taskList.at(0).getNameSize();

    for(const Task & item : taskList)
    {
        if(MaxSize < item.getNameSize())
        {
            MaxSize = item.getNameSize();
        }
    }

    return MaxSize;
}