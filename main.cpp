#include <iostream>
#include <string>
using namespace std;

//RESERVATION INFO BLUEPRINT (Like Java Class :3)
struct Reservation
{
    int id;
    string name;
    string address;
    int roomNumber;
    string checkIn;
    string checkOut;
    int guests;
};

int main(int argc, char **argv)
{
    Reservation add;

    int userChoice;
    string login = "admin";
    string password = "admin";
    string userLogin, userPW;

    int attempts = 0;
    bool authenticated = false;
    // LOGIN BLOCK
    while (attempts < 3)
    {
        cout << "Enter username: ";
        cin >> userLogin;

        cout << "Enter password: ";
        cin >> userPW;

        if (userLogin == login && userPW == password)
        {
            authenticated = true;
            break;
        }

        attempts++;
        cout << "Invalid credentials. Attempts left: " << (3 - attempts) << "\n\n";
    }

    if (!authenticated)
    {
        cout << "You are only allowed 3 attempts, sorry.\n";
        return 0;
    }

    cout << "\nWelcome back, " << userLogin << "!\n";

    // THE HOTEL RESERVATION MENU
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
            cout << "\n--------------------------------------";
            break;
        }
    }
}