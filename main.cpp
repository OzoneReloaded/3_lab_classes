#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Task
{
private:
    string name;
public:
    int percent_done;
        void define_name(int current_task)
        {
            cout << "Enter current " << current_task <<  " task name: ";
            cin >> this->name;
        }
        void define_completed_percentage(int current_task)
        {
            cout << "Enter " << current_task << " task percentage completed: ";
            cin >> this->percent_done;
        }
};

class Worker
{
private:
    string name;
    bool master = false;
    float basic_salary;
    int number_of_tasks;
    Task *Tasks = new Task[number_of_tasks];
    int number_of_completed_tasks = 0;
    int number_of_overcompleted_tasks = 0;
    int number_of_undercompleted_tasks = 0;
    float payday_salary = 0;
public:
    void enter_name()
    {
        cout << "Enter the worker's full name: " << endl;
        cin >> this->name;
    }
    void enter_qualification()
    {
        string entered;
        cout << "Enter the worker's qualification (master/novice):" << endl;
        cout << "Note: master acquires 10% additional basic salary." << endl;
        cin >> entered;
        if (entered == "master")
        {
            this->master = true;
        }
        else if (entered == "novice")
        {
            this->master = false;
        }
        else
        {
            cout << "Error. Try again." << endl;
            this->enter_qualification();
        }
    }
    void enter_basic_salary()
    {
        cout << "Enter the worker's basic salary: " << endl;
        cin >> this->basic_salary;
    }
    void define_static_task_number(int static_task_number)
    {
        this->number_of_tasks = static_task_number;
    }
    void cycle_through_tasks()
    {
        for (int current_task = 0; current_task<number_of_tasks; current_task++)
        {
            this->Tasks[current_task].define_name(current_task);
            this->Tasks[current_task].define_completed_percentage(current_task);
        }
    }
    void confirm_tasks()
    {
        cout << "Confirming the tasks..." << endl;
        for (int i = 0; i<number_of_tasks; i++)
        {
            if (this->Tasks[i].percent_done == 100)
                this->number_of_completed_tasks++;
            else if (this->Tasks[i].percent_done > 100)
                this->number_of_overcompleted_tasks++;
            else if (this->Tasks[i].percent_done < 100)
                this->number_of_undercompleted_tasks++;
        }
        cout << "Done." << endl;
    }
    void payday()
    {
        if ((this->number_of_undercompleted_tasks == 0) && (this->number_of_overcompleted_tasks > this->number_of_completed_tasks))
        {
            this->payday_salary = basic_salary + (basic_salary * 0.1);
            cout << "Additional 10% of basic salary acquired due to overcompleted tasks." << endl;
        }
        else if (this->number_of_undercompleted_tasks > 0)
        {
            this->payday_salary = basic_salary - (basic_salary * 0.1);
            cout << "Additional 10% fee acquired due to undercompleted tasks." << endl;
        }
        else
        {
            this->payday_salary = basic_salary;
        }
    }
    void qualification_payday_drift()
    {
        if (this->master == true)
        {
            payday_salary = payday_salary + (basic_salary * 0.1);
            cout << "Additional 10% of basic salary acquired due to mastership." << endl << endl;
            cout << "Payday salary is: " << payday_salary << endl;
        }
        else
        {
            cout << "Payday salary is: " << payday_salary << endl;
        }
    }
};

int main()
{
    cout << "Enter the exact number of workers: " << endl;
    int number_of_workers;
    cin >> number_of_workers;
    cout << "Enter the exact number of tasks: " << endl;
    int number_of_tasks;
    cin >> number_of_tasks;
    Worker Workers[number_of_workers];

    fstream file("i_want_to.die", ios::out | ios::binary);
    file.write((char*)&Workers, sizeof(Workers));
    file.close();

    fstream input_file("i_want_to.die", ios::in | ios::binary);
    Worker Workers_opened[number_of_workers];
    input_file.read((char*)&Workers_opened, sizeof(Workers_opened));

    for (int i = 0; i < number_of_workers; i++)
    {
        Workers_opened[i].enter_name();
        Workers_opened[i].enter_qualification();
        Workers_opened[i].enter_basic_salary();
        Workers_opened[i].define_static_task_number(number_of_tasks);
        Workers_opened[i].cycle_through_tasks();
        Workers_opened[i].confirm_tasks();
        Workers_opened[i].payday();
        Workers_opened[i].qualification_payday_drift();
    }


    return 0;
}
