#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    int userChoice;
    int attempts = 1;
    string login = "admin";
    string password = "admin";
    string userLogin;
    string userPW;

    cout << "Enter username: ";
    cin >> userLogin;
    cout << "Enter password: ";
    cin >> userPW;
    while (userPW != password && attempts <= 2)
    {
        cout << "\n";
        cout << "Password attempt: " << attempts + 1;
        cout << "\n";
        cout << "Enter password again: ";
        cin >> userPW;
        attempts++;
    }
    if (userPW == password && attempts <= 3)
    {
        cout << "\n";
        cout << "Welcome back! " << userLogin;
    }
    else
    {
        cout << "You are only allowed 3 attempts, sorry";
        cout << "\n";
        return 0;
    }
    while (true)
    {
        cout << "\n";
        cout << "\nMENU";
        cout << "\n1. Add";
        cout << "\n2. Edit";
        cout << "\n3. Delete";
        cout << "\n4. View";
        cout << "\n5. Save";
        cout << "\n6. Quit";
        cout << "\nOPTION: ";
        cin >> userChoice;
        switch (userChoice)
        {
        case 1:
            cout << "           New Reservation";
            cout << "\n--------------------------------------";
            cout << "\nCheck-in-date(dd/mm/yyyy): ";
            cout << "\nCheck-out-date(dd/mm/yyyy) :";
            cout << "\n";
            cout << "\nNumber of guest (max 20): ";
        }
    }
}