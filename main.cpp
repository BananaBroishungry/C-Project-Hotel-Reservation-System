#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// RESERVATION INFO BLUEPRINT
struct Reservation
{
    int id;
    string name;
    string contactNumber;
    int roomNumber;
    string checkIn;
    string checkOut;
    int guests;
};

// -----------------------------
// HELPER FUNCTIONS
// -----------------------------

vector<int> getHotelRooms()
{
    vector<int> rooms;

    for (int i = 101; i <= 110; i++)
        rooms.push_back(i);

    for (int i = 201; i <= 210; i++)
        rooms.push_back(i);

    for (int i = 301; i <= 310; i++)
        rooms.push_back(i);

    for (int i = 401; i <= 410; i++)
        rooms.push_back(i);

    for (int i = 501; i <= 510; i++)
        rooms.push_back(i);
    return rooms;
}

bool roomExists(int roomNumber)
{
    vector<int> rooms = getHotelRooms();

    for (int room : rooms)
    {
        if (room == roomNumber)
            return true;
    }

    return false;
}

bool isRoomOccupied(int roomNumber)
{
    ifstream file("reservations.txt");
    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;
        Reservation occupied;

        getline(ss, temp, ','); occupied.id = stoi(temp);
        getline(ss, occupied.name, ',');
        getline(ss, occupied.contactNumber, ',');
        getline(ss, temp, ','); occupied.roomNumber = stoi(temp);
        getline(ss, occupied.checkIn, ',');
        getline(ss, occupied.checkOut, ',');
        getline(ss, temp, ','); occupied.guests = stoi(temp);

        if (occupied.roomNumber == roomNumber)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Used in EDIT so the current reservation can keep its own room and so that we don't have duplicates :3
bool isRoomOccupiedByAnother(int roomNumber, int currentReservationID)
{
    ifstream file("reservations.txt");
    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;
        Reservation isOccupied;

        getline(ss, temp, ',');isOccupied.id = stoi(temp);
        getline(ss, isOccupied.name, ',');
        getline(ss, isOccupied.contactNumber, ',');
        getline(ss, temp, ','); isOccupied.roomNumber = stoi(temp);
        getline(ss, isOccupied.checkIn, ',');
        getline(ss, isOccupied.checkOut, ',');
        getline(ss, temp, ','); isOccupied.guests = stoi(temp);

        if (isOccupied.roomNumber == roomNumber && isOccupied.id != currentReservationID)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

int getNextReservationID()
{
    ifstream file("reservations.txt");
    string line;
    int maxID = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;
        getline(ss, temp, ',');
        int id = stoi(temp);

        if (id > maxID)
            maxID = id;
    }

    file.close();
    return maxID + 1;
}

void showAvailableRooms()
{
    vector<int> rooms = getHotelRooms();

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║          AVAILABLE ROOMS            ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    bool hasAvailable = false;

    for (int room : rooms)
    {
        if (!isRoomOccupied(room))
        {
            cout << "Room " << room << " [Available]\n";
            hasAvailable = true;
        }
    }

    if (!hasAvailable)
    {
        cout << "No available rooms at the moment.\n";
    }
}

string getRoomStatus(int roomNumber)
{
    if (isRoomOccupied(roomNumber))
        return "Occupied";
    return "Available";
}

// -----------------------------
// ADD MENU METHOD
// -----------------------------
void addReservation()
{
    string userSave;
    Reservation add;

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║              FRONT DESK              ║\n";
    cout << "║              GRAND HOTEL             ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║         Guest Check-In Form          ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    add.id = getNextReservationID();
    cout << "Reservation ID : " << add.id << "\n";

    cout << "\nGuest Name     : ";
    cin >> add.name;

    cout << "\nContact Number : ";
    cin >> add.contactNumber;

    showAvailableRooms();

    cout << "\nRoom Number    : ";
    while (true)
    {
        if (!(cin >> add.roomNumber))
        {
            cout << "Invalid input. Enter a valid room number: ";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (!roomExists(add.roomNumber))
        {
            cout << "That room does not exist. Enter another room: ";
            continue;
        }

        if (isRoomOccupied(add.roomNumber))
        {
            cout << "That room is already occupied. Choose another room: ";
            continue;
        }

        break;
    }

    cout << "\nCheck-In Date  : ";
    cin >> add.checkIn;

    cout << "\nCheck-out Date : ";
    cin >> add.checkOut;

    cout << "\nGuests         : ";
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

    if (userSave == "s" || userSave == "S")
    {
        ofstream file("reservations.txt", ios::app);

        file << add.id << ","
             << add.name << ","
             << add.contactNumber << ","
             << add.roomNumber << ","
             << add.checkIn << ","
             << add.checkOut << ","
             << add.guests << "\n";

        file.close();

        cout << "\n";
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║       CHECK-IN COMPLETED ✓           ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ Guest successfully registered.       ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }
    else if (userSave == "c" || userSave == "C")
    {
        cout << "\n";
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║       CHECK-IN CANCELLED ✕           ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ No reservation has been saved.       ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }
}

// -----------------------------
// VIEW MENU METHOD
// -----------------------------
void viewReservations()
{
    ifstream file("reservations.txt");
    string line;

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                        RESERVATION RECORDS                                     ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n";

    cout << "╔════╦══════════════╦══════════════╦══════╦════════════╦════════════╦════════╦════════════╗\n";
    cout << "║ ID ║ Name         ║ Contact No.  ║ Room ║ Check-In   ║ Check-Out  ║ Guests ║ Status     ║\n";
    cout << "╠════╬══════════════╬══════════════╬══════╬════════════╬════════════╬════════╬════════════╣\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;
        Reservation view;

        getline(ss, temp, ','); view.id = stoi(temp);
        getline(ss, view.name, ',');
        getline(ss, view.contactNumber, ',');
        getline(ss, temp, ','); view.roomNumber = stoi(temp);
        getline(ss, view.checkIn, ',');
        getline(ss, view.checkOut, ',');
        getline(ss, temp, ','); view.guests = stoi(temp);

        cout << "║ "
             << left << setw(2) << view.id << " ║ "
             << setw(12) << view.name << " ║ "
             << setw(12) << view.contactNumber << " ║ "
             << setw(4) << view.roomNumber << " ║ "
             << setw(10) << view.checkIn << " ║ "
             << setw(10) << view.checkOut << " ║ "
             << setw(6) << view.guests << " ║ "
             << setw(10) << getRoomStatus(view.roomNumber) << " ║\n";
    }

    cout << "╚════╩══════════════╩══════════════╩══════╩════════════╩════════════╩════════╩════════════╝\n";
    file.close();
}

// -----------------------------
// EDIT MENU METHOD
// -----------------------------
void editReservations()
{
    int userID;
    string line;

    ifstream file("reservations.txt");

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║         CURRENT RESERVATIONS         ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    cout << "\n╔════╦══════════════╦══════════════╦══════╦════════════╦════════════╦════════╗\n";
    cout << "║ ID ║ Name         ║ Contact No.  ║ Room ║ Check-In   ║ Check-Out  ║ Guests ║\n";
    cout << "╠════╬══════════════╬══════════════╬══════╬════════════╬════════════╬════════╣\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;
        Reservation preview;

        getline(ss, temp, ','); preview.id = stoi(temp);
        getline(ss, preview.name, ',');
        getline(ss, preview.contactNumber, ',');
        getline(ss, temp, ','); preview.roomNumber = stoi(temp);
        getline(ss, preview.checkIn, ',');
        getline(ss, preview.checkOut, ',');
        getline(ss, temp, ','); preview.guests = stoi(temp);

        cout << "║ "
             << setw(2) << left << preview.id << " ║ "
             << setw(12) << left << preview.name << " ║ "
             << setw(12) << left << preview.contactNumber << " ║ "
             << setw(4) << left << preview.roomNumber << " ║ "
             << setw(10) << left << preview.checkIn << " ║ "
             << setw(10) << left << preview.checkOut << " ║ "
             << setw(6) << left << preview.guests << " ║\n";
    }
    cout << "╚════╩══════════════╩══════════════╩══════╩════════════╩════════════╩════════╝\n";

    file.close();

    cout << "\nEnter ID to edit: ";
    cin >> userID;

    ifstream inFile("reservations.txt");
    ofstream outFile("temp.txt");

    Reservation edit;
    bool found = false;

    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;

        getline(ss, temp, ','); edit.id = stoi(temp);
        getline(ss, edit.name, ',');
        getline(ss, edit.contactNumber, ',');
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
            cout << "║ Contact No.: " << setw(20) << left << edit.contactNumber << "    ║\n";
            cout << "║ Room:        " << setw(20) << left << edit.roomNumber << "    ║\n";
            cout << "║ Status:      " << setw(20) << left << getRoomStatus(edit.roomNumber) << "    ║\n";
            cout << "║ Check-In:    " << setw(20) << left << edit.checkIn << "    ║\n";
            cout << "║ Check-Out:   " << setw(20) << left << edit.checkOut << "    ║\n";
            cout << "║ Guests:      " << setw(20) << left << edit.guests << "    ║\n";
            cout << "╚══════════════════════════════════════╝\n";

            cout << "\n--------------------------------------\n";
            cout << "Enter NEW values:\n\n";

            cout << "Name          : ";
            cin >> edit.name;

            cout << "Contact No.   : ";
            cin >> edit.contactNumber;

            cout << "Room          : ";
            while (true)
            {
                if (!(cin >> edit.roomNumber))
                {
                    cout << "Invalid input. Enter a valid room number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                if (!roomExists(edit.roomNumber))
                {
                    cout << "That room does not exist. Enter another room: ";
                    continue;
                }

                if (isRoomOccupiedByAnother(edit.roomNumber, edit.id))
                {
                    cout << "That room is already occupied. Choose another room: ";
                    continue;
                }

                break;
            }

            cout << "Check-In      : ";
            cin >> edit.checkIn;

            cout << "Check-Out     : ";
            cin >> edit.checkOut;

            cout << "Guests        : ";
            while (!(cin >> edit.guests))
            {
                cout << "Invalid input. Enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

        outFile << edit.id << ","
                << edit.name << ","
                << edit.contactNumber << ","
                << edit.roomNumber << ","
                << edit.checkIn << ","
                << edit.checkOut << ","
                << edit.guests << "\n";
    }

    inFile.close();
    outFile.close();

    string userSave;

    if (!found)
    {
        remove("temp.txt");
        cout << "\nID not found!\n";
        return;
    }

    cout << "\n--------------------------------------\n";
    cout << "[S] Save   [C] Cancel\n";
    cout << "Select option: ";
    cin >> userSave;

    if (userSave == "s" || userSave == "S")
    {
        remove("reservations.txt");
        rename("temp.txt", "reservations.txt");
        cout << "\nReservation updated successfully!\n";
    }
    else
    {
        remove("temp.txt");
        cout << "\nReservation cancelled...\n";
    }
}

// -----------------------------
// SEARCH MENU METHOD
// -----------------------------
void searchReservations()
{
    int searchID;
    string line;
    bool found = false;

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║          GRAND HOTEL                 ║\n";
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
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;
        Reservation search;

        getline(ss, temp, ','); search.id = stoi(temp);
        getline(ss, search.name, ',');
        getline(ss, search.contactNumber, ',');
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
            cout << "║ Contact No.: " << setw(20) << left << search.contactNumber << "    ║\n";
            cout << "║ Room:        " << setw(20) << left << search.roomNumber << "    ║\n";
            cout << "║ Status:      " << setw(20) << left << getRoomStatus(search.roomNumber) << "    ║\n";
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
        cout << "║        RESERVATION NOT FOUND ✕       ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║ No record matches this ID.           ║\n";
        cout << "╚══════════════════════════════════════╝\n";
    }
}

// -----------------------------
// DELETE MENU METHOD
// -----------------------------
void deleteReservations()
{
    int deleteID;
    string line;
    bool found = false;
    string userSave;

    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║         DELETE RESERVATION           ║\n";
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
        if (line.empty())
            continue;

        stringstream ss(line);
        string temp;

        getline(ss, temp, ','); del.id = stoi(temp);
        getline(ss, del.name, ',');
        getline(ss, del.contactNumber, ',');
        getline(ss, temp, ','); del.roomNumber = stoi(temp);
        getline(ss, del.checkIn, ',');
        getline(ss, del.checkOut, ',');
        getline(ss, temp, ','); del.guests = stoi(temp);

        if (del.id == deleteID)
        {
            found = true;

            cout << "\n╔══════════════════════════════════════╗\n";
            cout << "║        RESERVATION FOUND ✓           ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "║ ID:          " << setw(20) << left << del.id << "    ║\n";
            cout << "║ Name:        " << setw(20) << left << del.name << "    ║\n";
            cout << "║ Contact No.: " << setw(20) << left << del.contactNumber << "    ║\n";
            cout << "║ Room:        " << setw(20) << left << del.roomNumber << "    ║\n";
            cout << "║ Status:      " << setw(20) << left << getRoomStatus(del.roomNumber) << "    ║\n";
            cout << "║ Check-In:    " << setw(20) << left << del.checkIn << "    ║\n";
            cout << "║ Check-Out:   " << setw(20) << left << del.checkOut << "    ║\n";
            cout << "║ Guests:      " << setw(20) << left << del.guests << "    ║\n";
            cout << "╚══════════════════════════════════════╝\n";

            continue;
        }

        outFile << del.id << ","
                << del.name << ","
                << del.contactNumber << ","
                << del.roomNumber << ","
                << del.checkIn << ","
                << del.checkOut << ","
                << del.guests << "\n";
    }

    inFile.close();
    outFile.close();

    if (!found)
    {
        remove("temp.txt");
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║        RESERVATION NOT FOUND ✕       ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        return;
    }

    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║      CONFIRM DELETE ACTION           ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ [S] Yes, Delete Reservation          ║\n";
    cout << "║ [C] Cancel                           ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "Choice ► ";
    cin >> userSave;

    if (userSave == "s" || userSave == "S")
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
    cout << "║          Reservation System          ║\n";
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
        cout << "\nInvalid credentials!\n";
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
    cout << "║              " << userLogin << "                   ║\n";
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

            if (choice == "s" || choice == "S")
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
                cout << "║        GOODBYE, SEE YOU AGAIN!       ║\n";
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