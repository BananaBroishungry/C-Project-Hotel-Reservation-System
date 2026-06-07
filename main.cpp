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
    while (!(cin >> add.id)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "\nEnter Name: ";
    cin >> add.name;

    cout << "\nEnter Room Number: ";
    while (!(cin >> add.roomNumber)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "\nEnter Check-in Date: ";
    cin >> add.checkIn;

    cout << "\nEnter Check-out Date: ";
    cin >> add.checkOut;

    cout << "\nEnter Number of Guests: ";
    while (!(cin >> add.guests)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

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
        stringstream ss(line);
        string temp;

        Reservation view;

        getline(ss, temp, ',');
        view.id = stoi(temp);
        getline(ss, view.name, ',');
        getline(ss, temp, ',');
        view.roomNumber = stoi(temp);
        getline(ss, view.checkIn, ',');
        getline(ss, view.checkOut, ',');
        getline(ss, temp, ',');
        view.guests = stoi(temp);

        cout << "\nID " << view.id << "\n";
        cout << "\nName: " << view.name;
        cout << "\nRoom Number: " << view.roomNumber;
        cout << "\nCheck-in Date: " << view.checkIn;
        cout << "\nCheck-out Date: " << view.checkOut;
        cout << "\nNumber of Guests: " << view.guests << "\n";
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

        getline(ss, temp, ',');
        edit.id = stoi(temp);
        getline(ss, edit.name, ',');
        getline(ss, temp, ',');
        edit.roomNumber = stoi(temp);
        getline(ss, edit.checkIn, ',');
        getline(ss, edit.checkOut, ',');
        getline(ss, temp, ',');
        edit.guests = stoi(temp);

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
    else
    {
        cout << "\nID not found!\n";
    }
}
// SEARCH MENU METHOD
void searchReservations()
{
    int searchID;
    string line;
    bool found = false;

    ifstream file("reservations.txt");

    cout << "\nEnter ID to search: ";
    cin >> searchID;

    cout << "\n--- SEARCH RESULT ---\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;

        Reservation search;

        getline(ss, temp, ',');
        search.id = stoi(temp);
        getline(ss, search.name, ',');
        getline(ss, temp, ',');
        search.roomNumber = stoi(temp);
        getline(ss, search.checkIn, ',');
        getline(ss, search.checkOut, ',');
        getline(ss, temp, ',');
        search.guests = stoi(temp);

        if (search.id == searchID)
        {
            found = true;

            cout << "\nID " << search.id << "\n";
            cout << "\nName: " << search.name;
            cout << "\nRoom Number: " << search.roomNumber;
            cout << "\nCheck-in Date: " << search.checkIn;
            cout << "\nCheck-out Date: " << search.checkOut;
            cout << "\nNumber of Guests: " << search.guests << "\n";

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "ID not found!\n";
    }
}
// DELETE MENU METHOD
void deleteReservations()
{
    int deleteID;
    string line;
    bool found = false;

    ifstream inFile("reservations.txt");
    ofstream outFile("temp.txt");

    cout << "\nEnter ID to delete: ";
    cin >> deleteID;

    cout << "\n--- SEARCH RESULT ---\n";

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string temp;

        Reservation del;

        getline(ss, temp, ','); del.id = stoi(temp);
        getline(ss, del.name, ',');
        getline(ss, temp, ','); del.roomNumber = stoi(temp);
        getline(ss, del.checkIn, ',');
        getline(ss, del.checkOut, ',');
        getline(ss, temp, ','); del.guests = stoi(temp);

        if (del.id == deleteID)
        {
            found = true;
            continue;
        }

        outFile << del.id << ","
                << del.name << ","
                << del.roomNumber << ","
                << del.checkIn << ","
                << del.checkOut << ","
                << del.guests << "\n";
    }

    inFile.close();
    outFile.close();

    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    if (found) {
        cout << "\nReservation deleted successfully!\n";
    }
    else {
        cout << "\nID not found!\n";
    }
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
        cout << "║               MENU                   ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ 1. Add Reservation                   ║\n";
        cout << "║ 2. View Reservations                 ║\n";
        cout << "║ 3. Edit Reservation                  ║\n";
        cout << "║ 4. Delete Reservation                ║\n";
        cout << "║ 5. Search Reservation                ║\n";
        cout << "║ 6. Quit                              ║\n";
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
            deleteReservations();
            break;
        case 5:
            searchReservations();
            break;
        case 6:
            return 0;

        default:
            cout << "Invalid! Please try again...\n";
        }
    }
}
