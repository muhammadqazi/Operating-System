
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

//store data from file to linked list
typedef struct Node
{
    int process;
    int arrival_time;
    int burst_time;
    int priority;
    int turnaround_time;
    int waiting_time;
    int time_remaining;
    float average_time;
    struct Node *next;
} NODE;

NODE *head, *tail = NULL;

//validator
int Validator(int option, int startLimit, int endLimit)
{
    if ((option <= startLimit || option <= endLimit) && (option != 0))
    {
        return true;
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

int timeValidator(int time)
{
    if (time == 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    else
    {
        return true;
    }
}

void sortHandler(int method)
{

    NODE *current = head, *index = NULL;

    int temp, burst, prior;

    if (head == NULL)
    {
        return;
    }
    else
    {
        while (current != NULL)
        {
            index = current->next;

            while (index != NULL)
            {
                if (method == 1) //sort list according to arrival time
                {
                    if (current->arrival_time > index->arrival_time)
                    {
                        temp = current->arrival_time;
                        current->arrival_time = index->arrival_time;
                        index->arrival_time = temp;

                        burst = current->burst_time;
                        current->burst_time = index->burst_time;
                        index->burst_time = burst;

                        prior = current->priority;
                        current->priority = index->priority;
                        index->priority = prior;
                    }
                }
                else if (method == 2) //sort list according to burst time
                {
                    if (current->burst_time > index->burst_time)
                    {

                        burst = current->burst_time;
                        current->burst_time = index->burst_time;
                        index->burst_time = burst;

                        temp = current->arrival_time;
                        current->arrival_time = index->arrival_time;
                        index->arrival_time = temp;

                        prior = current->priority;
                        current->priority = index->priority;
                        index->priority = prior;
                    }
                }
                else if (method == 3) //sort list according to priority
                {
                    if (current->priority < index->priority)
                    {

                        prior = current->priority;
                        current->priority = index->priority;
                        index->priority = prior;

                        burst = current->burst_time;
                        current->burst_time = index->burst_time;
                        index->burst_time = burst;

                        temp = current->arrival_time;
                        current->arrival_time = index->arrival_time;
                        index->arrival_time = temp;
                    }
                }

                index = index->next;
            }
            current = current->next;
        }
    }
}

void RRScontroller(NODE *head, int time_quantum, int count)
{

    //round robin scheduling linked list
    sortHandler(1);

    head->waiting_time = 0;

    int current_time = 0;
    int i = 0;

    do
    {
        bool counter = true;

        while (head != NULL)
        {
            if (head->time_remaining > 0)
            {
                counter = false;

                if (head->time_remaining > time_quantum)
                {
                    current_time = current_time + time_quantum;

                    head->time_remaining -= time_quantum;

                    if (head->time_remaining < time_quantum)
                    {
                        current_time = current_time + head->time_remaining;

                        head->waiting_time = current_time - head->burst_time;

                        head->time_remaining = 0;
                    }
                }
            }
            i++;
            cout << "Waiting time for process " << i << " is " << head->waiting_time << endl;
            head = head->next;
        }
        if (counter == true)
            break;
    } while (true);
}

//insert data into the linked list
void insertHandler(NODE **head, int process, int arrival_time, int burst_time, int priority, int turnaround_time)
{

    NODE *point, *r = *head;
    point = (NODE *)malloc(sizeof(NODE));
    point->process = process;
    point->arrival_time = arrival_time;
    point->burst_time = burst_time;
    point->priority = priority;
    point->turnaround_time = turnaround_time;
    point->time_remaining = point->burst_time; //for round robin scenario

    point->next = NULL;
    if (*head == NULL)
        *head = point;
    else
    {
        while (r->next != NULL)
            r = r->next;
        r->next = point;
    }
}

void calculationController(NODE *point, int method)
{
    sortHandler(method);
    while (point != NULL)
    {
        point->waiting_time = point->turnaround_time - point->burst_time;
        point = point->next;
    }
}

//display the linked list
void outputHandler(NODE *p, int count)
{
    float totalWaitingTime = 0.0;
    while (p != NULL)
    {
        cout << "Waiting time for process " << p->process << " is " << p->waiting_time << endl;
        totalWaitingTime += p->waiting_time;
        p = p->next;
    }
    cout << "Average waiting time is " << totalWaitingTime / count;
}

void premtiveSJF(NODE *head, int count)
{

    int t = 0;
    int i = 0;
    int complete = 0;
    int time_taken;
    //sort linked list according to burst_time
    sortHandler(2);

    while (complete != count)
    {
        while (head != NULL)
        {

            head->time_remaining = head->time_remaining - 1;



            if(head->time_remaining == 0){
                complete++;

                time_taken = t + 1;

                head->waiting_time = time_taken - head->burst_time - head->arrival_time;

                

                cout << "Waiting time for process " << i+1 << " is " << head->waiting_time << endl;

                i++;
                head = head->next;
            }

            t++;
        }
        
    }
}
//main
int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     cout << "Type error: command line arguments missing for input and output file\nPlease read the documentation at https://github.com/muhammadqazi/Operating-System";
    //     cout << "\n\nType ./main -h for help [*]";

    //     return 1;
    // }
    // else if (argc == 2)
    // {
    //     if (strcmp(argv[1], "-h") == 0)
    //     {
    //         cout << "Commands:\n"
    //              << endl;
    //         cout << "-f <input file>\n";
    //         cout << "-o <output file>\n";
    //     }
    // }

    // else
    // {
    int i = 0;
    int count = 0;
    int chr = 0;
    int option;
    bool validate = true;
    int sum = 0;
    string data;

    ifstream input("input.txt");
    ifstream input2;
    input2.open("input.txt");

    //To know the length of lines of the file
    //number of lines in file = lenth of the array of struct

    while (!input2.eof())
    {
        getline(input2, data);

        count++;
    }

    //assigning values to structure processModel
    for (i = 0; i < count; i++)
    {
        int counter = 0;
        string burst_time, arrival, priority;
        getline(input, data);
        chr = data.length();

        for (int j = 0; j < chr; j++)
        {

            if (data[j] == ':')
            {
                counter++;
                continue;
            }
            if (counter == 0)
            {
                burst_time += data[j];
            }
            if (counter == 1)
            {
                arrival += data[j];
            }
            if (counter == 2)
            {
                priority += data[j];
            }
        }

        int burst, arrival2, prior;

        stringstream burstTime;
        burstTime << burst_time;
        burstTime >> burst;

        stringstream arrivalTime;
        arrivalTime << arrival;
        arrivalTime >> arrival2;

        stringstream priorityValue;
        priorityValue << priority;
        priorityValue >> prior;

        sum += burst;
        // head = insertController(head, i+1 , arrival2, burst, prior);
        insertHandler(&head, i + 1, arrival2, burst, prior, sum);
    }

    //Ask user to input method
    do
    {

        if (validate)
        {
            cout << "\nPlease choose from the given options below" << endl;
        }

        cout << "\n 1) Scheduling Method (None)" << endl;
        cout << "\n 2) Preemptive Mode " << endl;
        cout << "\n 3) Non-Preemptive Mode " << endl;
        cout << "\n 4) Show Result" << endl;
        cout << "\n 5) End Program\n"
             << endl;

        cout << "Option> ";

        cin >> option;

        //validator return false for not valid data
        validate = Validator(option, 1, 5);

        if (!validate)
        {
            cout << "\n Please enter the correct choice" << endl;
        }
        else
        {
            // 1)
            if (option == 1)
            {
                do
                {
                    cout << "\n 1) None: None of scheduling method chosen" << endl;
                    cout << "\n 2) First Come, First Served Scheduling" << endl;
                    cout << "\n 3) Shortest-Job-First Scheduling (NON-PREMITIVE)" << endl;
                    cout << "\n 4) Priority Scheduling (NON-PREMITIVE)" << endl;
                    cout << "\n 5) Round-Robin Scheduling\n"
                         << endl;

                    cout << "Option> ";

                    cin >> option;

                    validate = Validator(option, 1, 5);
                    if (!validate)
                    {
                        cout << "\n Please enter the correct choice" << endl;
                    }
                    else
                    {
                        // 1)
                        if (option == 1)
                        {
                            cout << "\nSelected option " << option;
                        }

                        // 2)
                        else if (option == 2)
                        {

                            calculationController(head, 1);

                            outputHandler(head, count);

                            // structSortHandler(pd, count, 1);

                            // SchedulerController(pd, count);
                        }
                        // 3)
                        else if (option == 3)
                        {

                            calculationController(head, 2);

                            outputHandler(head, count);

                            // structSortHandler(pd, count, 2);

                            // SchedulerController(pd, count);
                        }
                        // 4)
                        else if (option == 4)
                        {

                            calculationController(head, 3);

                            outputHandler(head, count);
                            // structSortHandler(pd, count, 3);

                            // SchedulerController(pd, count);
                        }
                        // 5)
                        else if (option == 5)
                        {
                            validate = true;
                            int timeQ;
                            do
                            {
                                if (validate)
                                {

                                    cout << "Please enter the Time Quantum \n";
                                }
                                cout << "Option> ";
                                cin >> timeQ;
                                cout << endl;

                                validate = timeValidator(timeQ);

                                if (!validate)
                                {

                                    cout << "\nPlease enter the valid Time Quantum \n";
                                }
                                else
                                {
                                    //store the burst time from struct to simple array
                                    // int burst_time[count];
                                    // int waitTime[count];
                                    // for (int i = 0; i < count; i++)
                                    // {
                                    //     // burst_time[i] = pd[i].burst_time;
                                    // }

                                    RRScontroller(head, timeQ, count);
                                }

                            } while (!validate);
                        }
                    }

                } while (!validate);
            }

            // 2)
            else if (option == 2)
            {
                premtiveSJF(head, count);
            }
            // 3)
            else if (option == 3)
            {
                cout << "\nSelected option " << option;
            }
            // 4)
            else if (option == 4)
            {
                cout << "\nSelected option " << option;
            }
            // 5)
            else if (option == 5)
            {
                cout << "Program is terminated sucessfully";
                break;
            }
        }

        //if the data is valid
        //the validator will send true i will make it false to break the loop
        //if the validator send false i will make it true to loop again

    } while (!validate);
    // }

    return 0;
}
