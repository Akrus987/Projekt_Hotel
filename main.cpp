#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include "BasicPasswordGenerator.h"
#include "BasicIterationModel.cpp"

int main()
{
    vector<vector<string>> data = readData("testing_ID.txt");
    vector<vector<string>> passwordFile = readData("testing_Passwords.txt");
    vector<vector<string>> reservations = readData("testing_rooms.txt");
    int choice=0;
    bool run=1;
    cout << "Welcome to Hotel!" << endl;
    cout << "--------------------------------" << endl;
    while (run)
    {
            cout << "1. Create account" << endl;
            cout << "2. Log in" << endl;
            cout << "3. Exit" << endl;
            cout << "--------------------------------" << endl;
            cout << "Chose option: ";
            cin >> choice;
        switch (choice)
        {
            case 1:
            {
                cout << "---Registration---" << endl;
                new_user(data,passwordFile);
                saveData("testing_ID.txt","testing_Passwords.txt",data,passwordFile);
                break;  
            }
            case 2:
            {
                cout << "---Log in---" << endl;
                string name, surname, password, current_user="NULL";
                
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter surname: ";
                cin >> surname;
                cout << "Enter password: ";
                cin >> password;
                current_user = login(passwordFile,getID(data,name,surname),password);
                cout << "--------------------------------" << endl;
                if (current_user == "NULL")
                {
                    break;
                }
                displayUser(data,current_user);
                if (getType(data,current_user)=="a")
                {
                    cout << "You are admin!" << endl;
                    cout << "1. Change user data" << endl;
                    cout << "2. Change reservations" << endl;
                    cout << "3. Log out" << endl;
                    cout  << endl;
                    cout << "--------------------------------" << endl;
                    cout << "Chose option: ";
                    cin >> choice;
                    switch(choice)
                    {
                        case 1:
                        {
                            cout << "Change user data" << endl;
                            listactiveID(data);
                            cout<<"Enter ID of user you want to change: ";
                            string ID;
                            cin>>ID;
                            updateGuestAdmin(data,passwordFile,ID);
                            saveData("testing_ID.txt","testing_Passwords.txt",data,passwordFile);
                            break;
                        }
                        case 2:
                        {
                            cout << "Change reservations" << endl;
                            listactiveID(reservations);
                            cout<<"Enter ID of user you want to change: " << endl;
                            string ID;
                            cout << "ID : room number : how many people : status : clean : start : end : name" << endl;
                            cin>>ID;
                            updateReservation(reservations,ID);
                            saveData("testing_rooms.txt","testing_Passwords.txt",reservations,passwordFile);       
                            break;
                        }
                        case 3:
                        {
                            cout << "Log out ;>" << endl;
                            break;
                        }
                        default:
                        {
                            cout << "Wrong choice!" << endl;
                            break;
                        }
                    }
                }

                else if (getType(data,current_user)=="g")
                {
                    cout << "1. Change your data" << endl;
                    cout << "2. Book a room" << endl;
                    cout << "3. Check your reservation" << endl;
                    cout << "4. Log out" << endl;
                    cout << "--------------------------------" << endl;
                    cout << "Chose option: ";
                    cin >> choice;
                    switch (choice)
                    {
                        case 1:
                        {
                            cout << "Change your data" << endl;
                            updateGuest(data,passwordFile,current_user);
                            saveData("testing_ID.txt","testing_Passwords.txt",data,passwordFile);
                            break;
                        }
                        case 2:
                        {
                            cout << "Book a room" << endl;
                            //bookRoom(data,current_user);
                            saveData("testing_ID.txt","testing_Passwords.txt",data,passwordFile);
                            break;
                        }
                        case 3:
                        {
                            cout << "Check your reservation" << endl;
                            //checkReservation(data,current_user);
                            break;
                        }
                        case 4:
                        {
                            cout << "Log out" << endl;
                            break;
                        }
                        default:
                        {
                            cout << "Wrong choice!" << endl;
                            break;
                        }
                    }
                }

                break;
            }
            case 3:
            {
                cout << "Thank you for using our service!" << endl;
                run=0;
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
