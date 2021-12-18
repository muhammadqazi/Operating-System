#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct processModel
{
    int burst_time;
    int arrival;
    int priority;
};

//store data from file to linked list
struct Node
{
    int process;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    float average_time;

    struct Node *next;
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

int main()
{
    struct Node *head;
    head = (struct Node *)malloc(sizeof(struct Node));

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

        head->process = i + 1;
        head->arrival_time = arrival2;
        head->burst_time = burst;
        head->priority = prior;
        head->average_time = 0;
        head->waiting_time = 0;
    }

    //printing the data from file
    cout << "Process\tArrival\tBurst\tPriority\n";
    for (i = 0; i < count; i++)
    {
        cout << head->process << "\t" << head->arrival_time << "\t" << head->burst_time << "\t" << head->priority << "\n";
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
