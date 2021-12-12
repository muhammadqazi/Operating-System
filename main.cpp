
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

        for (int i = 0; i < count - 1; i++)
        {
            cout<<pd[i].priority;
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
    for (i = 1; i < count; i++)
    {

        waitTime[i] = pd[i - 1].burst_time + waitTime[i - 1];
        cout << "Waiting time for process " << *(number + i) << " is " << waitTime[i] << " ms" << endl;
        averageWait += waitTime[i];
    }
    cout << "Average waiting time is " << averageWait / count;
}

//main
int main()
{
    int i = 0;
    int count;
    int option;
    bool validate = true;

    string data;
    string burst_time, arrival, priority;
    ifstream input("input.txt");
    ifstream input2("input.txt");

    //To know the length of lines of the file
    //number of lines in file = lenth of the array of struct

    if (!input.eof())
    {
        getline(input2, data);
        count = data.length();
    }

    struct processModel pd[count - 1];

    //assigning values to structure processModel
    while (!input.eof())
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

        //assigning int data
        pd[i].burst_time = burst;
        pd[i].arrival = arrival2;
        pd[i].priority = prior;

        i++;
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

                            structSortHandler(pd, count, 1);

                            SchedulerController(pd, count);
                        }
                        // 3)
                        else if (option == 3)
                        {

                            structSortHandler(pd, count, 2);

                            SchedulerController(pd, count);
                        }
                        // 4)
                        else if (option == 4)
                        {
                            structSortHandler(pd, count, 3);

                            SchedulerController(pd, count);
                        }
                        // 5)
                        else if (option == 5)
                        {
                            cout << "\nSelected option " << option;
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
