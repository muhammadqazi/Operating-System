
#include <iostream>
#include <limits>

using namespace std;

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

    int option;
    bool validate2;
    bool validate = true;
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
                cout << "\nSelected option " << option;
            }
        }

        //if the data is valid
        //the validator will send true i will make it false to break the loop
        //if the validator send false i will make it true to loop again

    } while (!validate);

    return 0;
}
