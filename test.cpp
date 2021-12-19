
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//process structure
struct processModel
{
    int burst_time;
    int arrival;
    int priority;
};

//store data from file to linked list
typedef struct Node
{
    int process;
    int arrival_time;
    int burst_time;
    int priority;
    int turnaround_time;
    int waiting_time;
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

//Round Robin Scheduler
void RRScontroller(int count, int burst_time[], int wait_time[], int timeQ)
{

    int time_remaining[count];
    for (int i = 0; i < count; i++)
    {

        time_remaining[i] = burst_time[i];
    }

    int time_now = 0;

    do
    {

        bool counter = true;

        for (int i = 0; i < count; i++)
        {

            if (time_remaining[i] > 0)
            {
                // if its greater then 0 we will set counter to false to perform the actions needed to complete the processes
                counter = false;
                if (time_remaining[i] > timeQ)
                {
                    time_now += timeQ;

                    time_remaining[i] -= timeQ;
                }

                else
                {
                    time_now += time_remaining[i];

                    wait_time[i] = time_now - burst_time[i];

                    //if the process is complete make the time 0
                    time_remaining[i] = 0;
                }
            }
        }

        //sending the program out of loop because we complete the process send to us
        if (counter == true)
            break;
    } while (true);

    double averageWait;
    for (int i = 0; i < count; i++)
    {
        cout << "Waiting time for " << (i + 1) << " is " << wait_time[i] << endl;
        averageWait += wait_time[i];
    }
    cout << "Average waiting time is " << averageWait / count;
}

int *sortHandler(int count, int arr[])
{
    int i;

    for (i = 0; i < count; i++)
    {
        arr[i] = count - i;
    }
    //sorting in order
    for (i = 0; i < count; i++)
    {
        for (i = 0; i < count - 1; i++)
        {

            for (int j = 0; j < count - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {

                    int temp = arr[j];

                    arr[j] = arr[j + 1];

                    arr[j + 1] = temp;
                }
            }
        }
    }
    return arr;
}

//struct sort handler if its 1 then according to arrival time if its 2 then according to burstTime if its 3 then according to priority
void structSortHandler(processModel *pd, int count, int method)
{
    //sort array according to arrivalTime
    if (method == 1)
    {
        for (int i = 0; i < count - 1; i++)
        {

            for (int j = 0; j < count - 1; j++)
            {
                if ((pd[j].arrival) > (pd[j + 1].arrival))
                {

                    int temp = pd[j].arrival;

                    pd[j].arrival = pd[j + 1].arrival;

                    pd[j + 1].arrival = temp;

                    int burst = pd[j].burst_time;

                    pd[j].burst_time = pd[j + 1].burst_time;

                    pd[j + 1].burst_time = burst;

                    int prior = pd[j].priority;

                    pd[j].priority = pd[j + 1].priority;

                    pd[j + 1].priority = prior;
                }
            }
        }
    }
    //sort array according to burstTime
    else if (method == 2)
    {

        for (int i = 0; i < count - 1; i++)
        {

            for (int j = 0; j < count - 1; j++)
            {
                if ((pd[j].burst_time) > (pd[j + 1].burst_time))
                {

                    int burst = pd[j].burst_time;

                    pd[j].burst_time = pd[j + 1].burst_time;

                    pd[j + 1].burst_time = burst;

                    int temp = pd[j].arrival;

                    pd[j].arrival = pd[j + 1].arrival;

                    pd[j + 1].arrival = temp;

                    int prior = pd[j].priority;

                    pd[j].priority = pd[j + 1].priority;

                    pd[j + 1].priority = prior;
                }
            }
        }
    }
    //sort array according to priority (decending order) greater the number greater is the priority
    else if (method == 3)
    {

        for (int i = 0; i < count - 1; i++)
        {

            for (int j = 0; j < count - 1; j++)
            {
                if ((pd[j].priority) < (pd[j + 1].priority))
                {

                    int prior = pd[j].priority;

                    pd[j].priority = pd[j + 1].priority;

                    pd[j + 1].priority = prior;

                    int burst = pd[j].burst_time;

                    pd[j].burst_time = pd[j + 1].burst_time;

                    pd[j + 1].burst_time = burst;

                    int temp = pd[j].arrival;

                    pd[j].arrival = pd[j + 1].arrival;

                    pd[j + 1].arrival = temp;
                }
            }
        }
    }
}

//Scheduler Method Controller
void SchedulerController(processModel *pd, int count)
{
    int i;
    int arr[count];

    //this will return a pointer for the array starting
    int *number = sortHandler(count, arr);

    //process name
    cout << "Waiting time for process " << 1 << " is 0 ms" << endl;
    int waitTime[count];
    waitTime[0] = 0;
    double averageWait;
    ofstream myfile;
    myfile.open("output.txt");
    for (i = 1; i < count; i++)
    {

        waitTime[i] = pd[i - 1].burst_time + waitTime[i - 1];
        cout << "Waiting time for process " << *(number + i) << " is " << waitTime[i] << " ms" << endl;
        averageWait += waitTime[i];

        myfile << "Waiting time for process " << *(number + i) << " is " << waitTime[i] << " ms" << endl;
    }
    cout << "Average waiting time is " << averageWait / count;
    myfile.close();
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
                if (method == 1)
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
                else if (method == 2)
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
                else if (method == 3)
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

//insert data into the linked list
void insertHandler(NODE **head, int process, int arrival_time, int burst_time, int priority, int turnaround_time)
{

    // CREATE NODE
    NODE *point, *r = *head;
    point = (NODE *)malloc(sizeof(NODE));
    point->process = process;
    point->arrival_time = arrival_time;
    point->burst_time = burst_time;
    point->priority = priority;
    point->turnaround_time = turnaround_time;
    // INSERT NODE AT END
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

//main
int main()
{

    int i = 0;
    int count = 0;
    int option;
    bool validate = true;
    int sum = 0;

    string data;
    string burst_time, arrival, priority;
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

        getline(input, data);
        //assigning strings
        burst_time = data[0];
        arrival = data[2];
        priority = data[4];

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
            cout << "Please choose from the given options below" << endl;
        }

        cout << "\n 1) Scheduling Method (None)" << endl;
        cout << "\n 2) Preemptive Mode (Off)" << endl;
        cout << "\n 3) Show Result" << endl;
        cout << "\n 4) End Program\n"
             << endl;

        cout << "Option> ";

        cin >> option;

        //validator return false for not valid data
        validate = Validator(option, 1, 4);

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
                    cout << "\n 3) Shortest-Job-First Scheduling" << endl;
                    cout << "\n 4) Priority Scheduling" << endl;
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
                            // validate = true;
                            // int timeQ;
                            // do
                            // {
                            //     if (validate)
                            //     {

                            //         cout << "Please enter the Time Quantum \n";
                            //     }
                            //     cout << "Option> ";
                            //     cin >> timeQ;
                            //     cout << endl;

                            //     validate = timeValidator(timeQ);

                            //     if (!validate)
                            //     {

                            //         cout << "\nPlease enter the valid Time Quantum \n";
                            //     }
                            //     else
                            //     {
                            //         //store the burst time from struct to simple array
                            //         int burst_time[count];
                            //         int waitTime[count];
                            //         for (int i = 0; i < count; i++)
                            //         {
                            //             burst_time[i] = pd[i].burst_time;
                            //         }

                            //         RRScontroller(count, burst_time, waitTime, timeQ);
                            //     }

                            // } while (!validate);
                        }
                    }

                } while (!validate);
            }

            // 2)
            else if (option == 2)
            {
                cout << "\nSelected option " << option;
            }
            // 3)
            else if (option == 3)
            {
                cout << "\nSelected option " << option;
            }
            // 4)
            else if (option == 4)
            {
                cout << "Program is terminated sucessfully";
                break;
            }
        }

        //if the data is valid
        //the validator will send true i will make it false to break the loop
        //if the validator send false i will make it true to loop again

    } while (!validate);

    return 0;
}
