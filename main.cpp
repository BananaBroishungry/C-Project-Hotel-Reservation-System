#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
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
    string userSave;
    Reservation add;

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║              🛎️ FRONT DESK           ║\n";
    cout << "║              GRAND HOTEL             ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║         Guest Check-In Form          ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "Reservation ID : ";

    
    while (!(cin >> add.id))
    {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "\nGuest Name     : ";
    cin >> add.name;

    cout << "\nRoom Number    : ";
    while (!(cin >> add.roomNumber))
    {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "\nCheck-In Date  : ";
    cin >> add.checkIn;

    cout << "\nCheck-out Date: ";
    cin >> add.checkOut;

    cout << "\nGuests: ";
    while (!(cin >> add.guests))
    {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║            FRONT DESK                ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║      Would you like to proceed?      ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "[S] Complete Check-In\n";
    cout << "[C] Cancel Check-In\n\n";

    cout << "Select Option: ";
    cin >> userSave;

    if (userSave == "s")
    {
        ofstream file("reservations.txt", ios::app);

        file << add.id << ","
             << add.name << ","
             << add.roomNumber << ","
             << add.checkIn << ","
             << add.checkOut << ","
             << add.guests << "\n";

        file.close();

        cout << "\n";
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║       CHECK-IN COMPLETED ✓          ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ Guest successfully registered.       ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }
    else if (userSave == "c")
    {
        cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       CHECK-IN CANCELLED ✕          ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ No reservation has been saved.       ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    }
}

// VIEW MENU METHOD
void viewReservations()
{
    ifstream file("reservations.txt");

    string line;

    cout << "\n";
    cout << "╔══════════════════════════════════════════════╗\n";
    cout << "║            RESERVATION RECORDS               ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n"; 
    
    cout << "\n╔════╦══════════════╦══════╦════════════╦════════════╦════════╗\n";
    cout << "║ ID ║ Name         ║ Room ║ Check-In   ║ Check-Out  ║ Guests ║\n";
    cout << "╠════╬══════════════╬══════╬════════════╬════════════╬════════╣\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;

        Reservation view;

        getline(ss, temp, ','); view.id = stoi(temp);
        getline(ss, view.name, ',');
        getline(ss, temp, ','); view.roomNumber = stoi(temp);
        getline(ss, view.checkIn, ',');
        getline(ss, view.checkOut, ',');
        getline(ss, temp, ','); view.guests = stoi(temp);

    cout << "║ "
        << left << setw(2) << view.id << " ║ "
        << setw(12) << view.name << " ║ "
        << setw(4) << view.roomNumber << " ║ "
        << setw(10) << view.checkIn << " ║ "
        << setw(10) << view.checkOut << " ║ "
        << setw(6) << view.guests << " ║\n";
    }

    cout << "╚════╩══════════════╩══════╩════════════╩════════════╩════════╝\n";
    file.close();
}

// EDIT MENU METHOD
void editReservations()
{
    int userID;
    string line;

    ifstream file("reservations.txt");

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║         CURRENT RESERVATIONS         ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    cout << "\n╔═════╦══════════════╦══════╦════════════╦════════════╦════════╗\n";
    cout << "║ ID  ║ Name         ║ Room ║ Check-In   ║ Check-Out  ║ Guests ║\n";
    cout << "╠═════╬══════════════╬══════╬════════════╬════════════╬════════╣\n";

    while (getline(file, line))
    {   
        stringstream ss(line);
        string temp;
        Reservation preview;
        
        getline(ss, temp, ','); preview.id = stoi(temp);
        getline(ss, preview.name, ',');
        getline(ss, temp, ','); preview.roomNumber = stoi(temp);
        getline(ss, preview.checkIn, ',');
        getline(ss, preview.checkOut, ',');
        getline(ss, temp, ','); preview.guests = stoi(temp);

        cout << "║ "
     << setw(3)  << left << preview.id << " ║ "
     << setw(12) << left << preview.name << " ║ "
     << setw(4)  << left << preview.roomNumber << " ║ "
     << setw(10) << left << preview.checkIn << " ║ "
     << setw(10) << left << preview.checkOut << " ║ "
     << setw(6)  << left << preview.guests << " ║\n";
    }
    cout << "╚═════╩══════════════╩══════╩════════════╩════════════╩════════╝\n";

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

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║         RESERVATION FOUND ✓          ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ ID:          " << setw(20) << left << edit.id << "    ║\n";
    cout << "║ Name:        " << setw(20) << left << edit.name << "    ║\n";
    cout << "║ Room:        " << setw(20) << left << edit.roomNumber << "    ║\n";
    cout << "║ Check-In:    " << setw(20) << left << edit.checkIn << "    ║\n";
    cout << "║ Check-Out:   " << setw(20) << left << edit.checkOut << "    ║\n";
    cout << "║ Guests:      " << setw(20) << left << edit.guests << "    ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    cout << "\n--------------------------------------\n";
    cout << "Enter NEW values:\n\n";

    cout << "Name       : ";
    cin >> edit.name;

    cout << "Room       : ";
    cin >> edit.roomNumber;

    cout << "Check-In   : ";
    cin >> edit.checkIn;

    cout << "Check-Out  : ";
    cin >> edit.checkOut;

    cout << "Guests     : ";
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

    string userSave;

    cout << "\n--------------------------------------\n";
    cout << "[S] Save   [C] Cancel\n";
    cout << "Select option: ";
    cin >> userSave;

    if (userSave == "s")
    {
        remove("reservations.txt");
        rename("temp.txt", "reservations.txt");
        cout << ("\nChanges saved!\n");
    }
    else
    {
        remove("temp.txt");
        cout << "\nReservation cancelled...\n";
    }
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

   cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║          🏨 GRAND HOTEL              ║\n";
    cout << "║          GUEST SEARCH PANEL          ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ Please enter Reservation ID below:   ║\n";
    cout << "║                                      ║\n";
    cout << "║   ID:  ";

    cin >> searchID;

    cout << "║                                      ║\n";
    cout << "╚══════════════════════════════════════╝\n";


    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║           SEARCHING SYSTEM...        ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "Accessing database";

    for (int i = 0; i < 4; i++)
    {
        Sleep(400);
        cout << ".";
    }

    cout << "\nMatching records...\n";
    Sleep(800);

    ifstream file("reservations.txt");

    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        Reservation search;

        getline(ss, temp, ','); search.id = stoi(temp);
        getline(ss, search.name, ',');
        getline(ss, temp, ','); search.roomNumber = stoi(temp);
        getline(ss, search.checkIn, ',');
        getline(ss, search.checkOut, ',');
        getline(ss, temp, ','); search.guests = stoi(temp);

        if (search.id == searchID)
        {
            found = true;

            cout << "╔══════════════════════════════════════╗\n";
            cout << "║        RESERVATION FOUND ✓           ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "║ ID:          " << setw(20) << left << search.id << "    ║\n";
            cout << "║ Name:        " << setw(20) << left << search.name << "    ║\n";
            cout << "║ Room:        " << setw(20) << left << search.roomNumber << "    ║\n";
            cout << "║ Check-In:    " << setw(20) << left << search.checkIn << "    ║\n";
            cout << "║ Check-Out:   " << setw(20) << left << search.checkOut << "    ║\n";
            cout << "║ Guests:      " << setw(20) << left << search.guests << "    ║\n";
            cout << "╚══════════════════════════════════════╝\n";

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║        RESERVATION NOT FOUND ✕      ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ No record matches this ID.          ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }
}


// DELETE MENU METHOD
void deleteReservations()
{
    int deleteID;
    string line;
    bool found = false;
    string userSave;

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║         🗑 DELETE RESERVATION        ║\n";
    cout << "║         GRAND HOTEL SYSTEM           ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ Enter Reservation ID below:          ║\n";
    cout << "║                                      ║\n";
    cout << "║   ID:  ";

    cin >> deleteID;

    cout << "║                                      ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║        VERIFYING RECORD...           ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "Searching...";

    for (int i = 0; i < 3; i++)
    {
        Sleep(500);
        cout << ".";
    }
    cout << "\n";

    ifstream inFile("reservations.txt");
    ofstream outFile("temp.txt");

    Reservation del;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ','); del.id = stoi(temp);
        getline(ss, del.name, ',');
        getline(ss, temp, ','); del.roomNumber = stoi(temp);
        getline(ss, del.checkIn, ',');
        getline(ss, del.checkOut, ',');
        getline(ss, temp, ','); del.guests = stoi(temp);

        if (del.id == deleteID)
        {
            found = true;

            cout << "\n╔══════════════════════════════════════╗\n";
            cout << "║        RESERVATION FOUND ✓            ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "║ ID:          " << setw(20) << left << del.id << "    ║\n";
            cout << "║ Name:        " << setw(20) << left << del.name << "    ║\n";
            cout << "║ Room:        " << setw(20) << left << del.roomNumber << "    ║\n";
            cout << "║ Check-In:    " << setw(20) << left << del.checkIn << "    ║\n";
            cout << "║ Check-Out:   " << setw(20) << left << del.checkOut << "    ║\n";
            cout << "║ Guests:      " << setw(20) << left << del.guests << "    ║\n";
            cout << "╚══════════════════════════════════════╝\n";

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

    // ❗ confirmation UI
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║      CONFIRM DELETE ACTION           ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ [S] Yes, Delete Reservation          ║\n";
    cout << "║ [C] Cancel                           ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "Choice ► ";
    cin >> userSave;

    if (userSave == "s")
    {
        cout << "\nDeleting record...";

        for (int i = 0; i < 4; i++)
        {
            Sleep(400);
            cout << ".";
        }

        remove("reservations.txt");
        rename("temp.txt", "reservations.txt");

        cout << "\n\n╔══════════════════════════════════════╗\n";
        cout << "║     DELETION SUCCESSFUL ✓            ║\n";
        cout << "║     Record removed from system       ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }
    else
    {
        remove("temp.txt");

        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║        OPERATION CANCELLED ✕         ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }

    if (!found)
    {
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║        RESERVATION NOT FOUND ✕      ║\n";
        cout << "╚══════════════════════════════════════╝\n";
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
    cout << "║          ˗ˏˋ ꒰ ✉︎ ꒱ ˎˊ˗             ║\n";
    cout << "║       Reservation Management         ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    // LOGIN BLOCK
    while (attempts < 3)
    {
        cout << "► Username: ";
        cin >> userLogin;

        cout << "► Password: ";
        cin >> userPW;

        if (userLogin == login && userPW == password)
        {
            authenticated = true;
            break;
        }

        attempts++;
        cout << "\n⚠ Invalid credentials!\n";
        cout << "Remaining Attempts: " << (3 - attempts) << "\n";
    }

    if (!authenticated)
    {
        cout << "You are only allowed 3 attempts, sorry.\n";
        return 0;
    }

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║          LOGIN SUCCESSFUL ✓          ║\n";
    cout << "║                                      ║\n";
    cout << "║       Welcome to Grand Hotel,        ║\n";
    cout << "║              " << userLogin;
    cout << "                   ║\n";
    cout << "╚══════════════════════════════════════╝\n";   

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
{
    string choice;

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║           EXIT SYSTEM                ║\n";
    cout << "║           GRAND HOTEL                ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ Are you sure you want to quit?       ║\n";
    cout << "║                                      ║\n";
    cout << "║   [S] Yes, Exit                      ║\n";
    cout << "║   [C] Cancel                         ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "Choice: ";
    cin >> choice;

    if (choice == "s")
    {
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║        CLOSING SYSTEM...             ║\n";
        cout << "╚══════════════════════════════════════╝\n\n";

        cout << "Saving session";

        for (int i = 0; i < 4; i++)
        {
            Sleep(400);
            cout << ".";
        }

        cout << "\n\n╔══════════════════════════════════════╗\n";
        cout << "║        GOODBYE, SEE YOU AGAIN !      ║\n";
        cout << "║        GRAND HOTEL SYSTEM CLOSED     ║\n";
        cout << "╚══════════════════════════════════════╝\n";

        Sleep(1200);
        return 0;
    }
    else
    {
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║        EXIT CANCELLED ✕              ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }

    break;
}

        default:
            cout << "Invalid! Please try again...\n";
        }
    }
}
