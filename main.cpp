
#include <iostream>
#include <limits>

using namespace std;

int Validator(int option)
{
    if (option == 1 || option == 2 || option == 3 || option == 4)
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
        validate = Validator(option);

        if (!validate)
        {
            cout << "\n Please enter the correct choice" << endl;
        }

        //if the data is valid 
        //the validator will send true i will make it false to break the loop
        //if the validator send false i will make it true to loop again
        
    } while (!validate);

    return 0;
}
