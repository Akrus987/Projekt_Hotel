#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include "BasicPasswordGenerator.h"
#include "BasicIterationModel.cpp"

using namespace std;

// Function to check reservation details
void checkReservation(vector<vector<string>>& data, vector<vector<string>>& reservations, const string& ID);

int main()
{
    // Load data from files
    vector<vector<string>> data = readData("testing_ID.txt");
    vector<vector<string>> passwordFile = readData("testing_Passwords.txt");
    vector<vector<string>> reservations = readData("testing_rooms.txt");

    int choice = 0;
    bool run = true;
    cout << "Welcome to Hotel!" << endl;
    cout << "--------------------------------" << endl;

    while (run)
    {
        // Display main menu
        cout << "1. Create account" << endl;
        cout << "2. Log in" << endl;
        cout << "3. Exit" << endl;
        cout << "--------------------------------" << endl;
        cout << "Choose option: ";
        cin >> choice;

        // Validate input
        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                cout << "---Registration---" << endl;
                try {
                    new_user(data, passwordFile);
                    saveData("testing_ID.txt", "testing_Passwords.txt", data, passwordFile);
                } catch (const exception& e) {
                    cout << "Error during registration: " << e.what() << endl;
                }
                break;
            }
            case 2:
            {
                cout << "---Log in---" << endl;
                string name, surname, password, current_user = "NULL";

                cout << "Enter name: ";
                cin >> name;
                cout << "Enter surname: ";
                cin >> surname;
                cout << "Enter password: ";
                cin >> password;

                try {
                    current_user = login(passwordFile, getID(data, name, surname), password);
                } catch (const exception& e) {
                    cout << "Error during login: " << e.what() << endl;
                    break;
                }

                cout << "--------------------------------" << endl;
                if (current_user == "NULL")
                {
                    cout << "Login failed. Please check your credentials." << endl;
                    break;
                }

                bool loggedIn = true;
                while (loggedIn)
                {
                    displayUser(data, current_user);
                    if (getType(data, current_user) == "a")
                    {
                        // Admin menu
                        cout << "You are admin!" << endl;
                        cout << "1. Change user data" << endl;
                        cout << "2. Change reservations" << endl;
                        cout << "3. Log out" << endl;
                        cout << "--------------------------------" << endl;
                        cout << "Choose option: ";
                        cin >> choice;

                        // Validate input
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number." << endl;
                            continue;
                        }

                        switch (choice)
                        {
                            case 1:
                            {
                                cout << "Change user data" << endl;
                                listactiveID(data);
                                cout << "Enter ID of user you want to change: ";
                                string ID;
                                cin >> ID;
                                try {
                                    updateGuestAdmin(data, passwordFile, ID);
                                    saveData("testing_ID.txt", "testing_Passwords.txt", data, passwordFile);
                                } catch (const exception& e) {
                                    cout << "Error updating user data: " << e.what() << endl;
                                }
                                break;
                            }
                            case 2:
                            {
                                cout << "Change reservations" << endl;
                                listactiveID(reservations);
                                cout << "Enter ID of user you want to change: ";
                                string ID;
                                cout << "ID : room number : how many people : status : clean : start : end : name" << endl;
                                cin >> ID;
                                try {
                                    updateReservation(reservations, ID);
                                    saveData("testing_rooms.txt", "testing_Passwords.txt", reservations, passwordFile);
                                } catch (const exception& e) {
                                    cout << "Error updating reservation: " << e.what() << endl;
                                }
                                break;
                            }
                            case 3:
                            {
                                cout << "Logging out..." << endl;
                                loggedIn = false;
                                break;
                            }
                            default:
                            {
                                cout << "Wrong choice!" << endl;
                                break;
                            }
                        }
                    }
                    else if (getType(data, current_user) == "g")
                    {
                        // Guest menu
                        cout << "1. Change your data" << endl;
                        cout << "2. Book a room" << endl;
                        cout << "3. Check your reservation" << endl;
                        cout << "4. Log out" << endl;
                        cout << "--------------------------------" << endl;
                        cout << "Choose option: ";
                        cin >> choice;

                        // Validate input
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number." << endl;
                            continue;
                        }

                        switch (choice)
                        {
                            case 1:
                            {
                                cout << "Change your data" << endl;
                                try {
                                    updateGuest(data, passwordFile, current_user);
                                    saveData("testing_ID.txt", "testing_Passwords.txt", data, passwordFile);
                                } catch (const exception& e) {
                                    cout << "Error updating data: " << e.what() << endl;
                                }
                                break;
                            }
                            case 2:
                            {
                                cout << "Book a room" << endl;
                                try {
                                    bookRoom(data, reservations, current_user);
                                    saveData("testing_ID.txt", "testing_Passwords.txt", data, passwordFile);
                                    saveData("testing_rooms.txt", "testing_Passwords.txt", reservations, passwordFile);
                                } catch (const exception& e) {
                                    cout << "Error booking room: " << e.what() << endl;
                                }
                                break;
                            }
                            case 3:
                            {
                                cout << "Check your reservation" << endl;
                                try {
                                    checkReservation(data, reservations, current_user);
                                    saveData("testing_rooms.txt", "testing_Passwords.txt", reservations, passwordFile);
                                    saveData("testing_ID.txt", "testing_Passwords.txt", data, passwordFile);
                                } catch (const exception& e) {
                                    cout << "Error checking reservation: " << e.what() << endl;
                                }
                                break;
                            }
                            case 4:
                            {
                                cout << "Logging out..." << endl;
                                loggedIn = false;
                                break;
                            }
                            default:
                            {
                                cout << "Wrong choice!" << endl;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 3:
            {
                cout << "Thank you for using our service!" << endl;
                run = false;
                break;
            }
            default:
            {
                cout << "Wrong choice!" << endl;
                break;
            }
        }
    }

    return 0;
}