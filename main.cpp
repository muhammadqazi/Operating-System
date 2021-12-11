
#include <iostream>
#include <limits>
#include <fstream>
#include <string>

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

//sort helper

void FCFScontroller(processModel *pd,int count)
{
    int i;
    int arr[count];
    //array filling with numbers of processes
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
    //process name
    cout << "Waiting time for process " << 1 << " is 0 ms" << endl;
    int waitTime[count];
    waitTime[0] = 0;
    for (i = 1; i < count; i++)
    {

        waitTime[i] = pd[i - 1].burst_time + waitTime[i - 1];
        cout << "Waiting time for process " << arr[i] << " is " << waitTime[i] << " ms" << endl;
    }
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

        //assigning int data
        pd[i].burst_time = stoi(burst_time);
        pd[i].arrival = stoi(arrival);
        pd[i].priority = stoi(priority);

        i++;
    }

    //sort array according to arrival time
    for (i = 0; i < count - 1; i++)
    {

        for (int j = 0; j < count - 1; j++)
        {
            if ((pd[j].arrival) > (pd[j + 1].arrival))
            {

                int temp = pd[j].arrival;

                pd[j].arrival = pd[j + 1].arrival;

                pd[j + 1].arrival = temp;
            }
        }
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
        cout << "\n 4) End Program" << endl;

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
                    cout << "\n 5) Round-Robin Scheduling" << endl;

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

                            FCFScontroller(pd,count);
                            // int i;
                            // int arr[count];
                            // //array filling with numbers of processes
                            // for (i = 0; i < count; i++)
                            // {
                            //     arr[i] = count - i;
                            // }
                            // //sorting in order
                            // for (i = 0; i < count; i++)
                            // {
                            //     for (i = 0; i < count - 1; i++)
                            //     {

                            //         for (int j = 0; j < count - 1; j++)
                            //         {
                            //             if (arr[j] > arr[j + 1])
                            //             {

                            //                 int temp = arr[j];

                            //                 arr[j] = arr[j + 1];

                            //                 arr[j + 1] = temp;
                            //             }
                            //         }
                            //     }
                            // }
                            // //process name
                            // cout << "Waiting time for process " << 1 << " is 0 ms" << endl;
                            // int waitTime[count];
                            // waitTime[0] = 0;
                            // for (i = 1; i < count; i++)
                            // {

                            //     waitTime[i] = pd[i - 1].burst_time + waitTime[i - 1];
                            //     cout << "Waiting time for process " << arr[i] << " is " << waitTime[i] << " ms" << endl;
                            // }
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
                cout << "\nSelected option " << option;
            }
        }

        //if the data is valid
        //the validator will send true i will make it false to break the loop
        //if the validator send false i will make it true to loop again

    } while (!validate);

    return 0;
}
