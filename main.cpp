#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;

// RESERVATION INFO BLUEPRINT (Like Java Class :3)
struct Reservation
{
    int id;
    string name;
    int roomNumber;
    string checkIn;
    string checkOut;
    int guests;
};

// ADD MENU METHOD
void addReservation()
{
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

// VIEW MENU METHOD
void viewReservations()
{
    ifstream file("reservations.txt");

    string line;

    cout << "\n--- ALL RESERVATIONS ---\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

// EDIT MENU METHOD
void editReservations()
{
    int userID;
    string line;

    ifstream file("reservations.txt");

    cout << "\n--- CURRENT RESERVATIONS ---\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    cout << "\nEnter ID to edit: ";
    cin >> userID;

    ifstream inFile("reservations.txt");
    ofstream outFile("temp.txt");

    Reservation edit;

    bool found = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ','); edit.id = stoi(temp);
        getline(ss, edit.name, ',');
        getline(ss, temp, ','); edit.roomNumber = stoi(temp);
        getline(ss, edit.checkIn, ',');
        getline(ss, edit.checkOut, ',');
        getline(ss, temp, ','); edit.guests = stoi(temp);

        if (edit.id == userID)
        {
            found = true;

            cout << "\nEditing Reservation ID " << userID << "\n";

            cout << "\nEnter new Name: ";
            cin >> edit.name;

            cout << "\nEnter new Room Number: ";
            cin >> edit.roomNumber;

            cout << "\nEnter new Check-in Date: ";
            cin >> edit.checkIn;

            cout << "\nEnter new Check-out Date: ";
            cin >> edit.checkOut;

            cout << "\nEnter new Number of Guests: ";
            cin >> edit.guests;
        }

        outFile << edit.id << ","
                << edit.name << ","
                << edit.roomNumber << ","
                << edit.checkIn << ","
                << edit.checkOut << ","
                << edit.guests << "\n";
    }

    inFile.close();
    outFile.close();

    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    if (found)
    {
        cout << "\nReservation updated successfully!";
    }
    else {
        cout << "\nID not found!\n";}
}

int main(int argc, char **argv)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int userChoice;
    string login = "admin";
    string password = "admin";
    string userLogin, userPW;

    int attempts = 0;
    bool authenticated = false;

    cout << "╔══════════════════════════════════════╗\n";
    cout << "║          ★ GRAND HOTEL ★             ║\n";
    cout << "║           ˗ˏˋ ꒰ ✉︎ ꒱ ˎˊ˗            ║\n";
    cout << "║       Reservation Management         ║\n";
    cout << "╚══════════════════════════════════════╝\n";


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
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║               MENU                  ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ 1. Add Reservation                  ║\n";
        cout << "║ 2. View Reservations                ║\n";
        cout << "║ 3. Edit Reservation                 ║\n";
        cout << "║ 4. Delete Reservation               ║\n";
        cout << "║ 5. Search Reservation               ║\n";
        cout << "║ 6. Quit                             ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        cout << "Option: ";
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
        case 3:
            editReservations();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            return 0;

        default:
            cout << "Invalid! Please try again...\n";
        }
    }
}
