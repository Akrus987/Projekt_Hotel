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
