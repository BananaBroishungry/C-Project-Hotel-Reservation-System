#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//RESERVATION INFO BLUEPRINT (Like Java Class :3)
struct Reservation
{
    int id;
    string name;
    int roomNumber;
    string checkIn;
    string checkOut;
    int guests;
};

//ADD MENU METHOD
void addReservation() {
    Reservation add;

    cout << "\nEnter ID: ";
    cin >> add.id;

    cout << "\nEnter Name: ";
    cin >> add.name;

    cout << "\nEnter Room Number: ";
    cin >> add.roomNumber;

    cout << "\nEnter Check-in Date: ";
    cin >> add.checkIn;

    cout << "\nEnter Check-out Date: ";
    cin >> add.checkOut;

    cout << "\nEnter Number of Guests: ";
    cin >> add.guests;

    ofstream file("reservations.txt", ios::app);

    file << add.id << ","
         << add.name << ","
         << add.roomNumber << ","
         << add.checkIn << ","
         << add.checkOut << ","
         << add.guests << "\n";

    file.close();

    cout << "\nReservation saved!\n";
}

//VIEW MENU METHOD
void viewReservations() {
    ifstream file("reservations.txt");

    string line;

    cout << "\n--- ALL RESERVATIONS ---\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

int main(int argc, char **argv)
{
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
        cout << "\n2. View";
        cout << "\n3. Edit";
        cout << "\n4. Delete";
        cout << "\n6. Quit";
        cout << "\nOPTION: ";
        cin >> userChoice;
        switch (userChoice)
        {
        case 1:
            cout << "           New Reservation";
            cout << "\n--------------------------------------";
            addReservation();
            cout << "\n--------------------------------------";
            break;
        case 2:
            viewReservations();
            break;
        }
    }
}

