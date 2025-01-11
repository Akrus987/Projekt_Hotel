// BasicPasswordGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

string GeneratePassword(string IDx)
{
    ifstream inFile("testing_ID.txt");
    if (!inFile) {
        cerr << "Unable to open file testing_ID.txt" << endl;
        exit(1); // terminate with error
    }

    string x, ID = IDx, name, surname;
    while (inFile >> x) 
    {
        if (x == ID)
        {
            inFile >> name >> surname;
            string newPassword, generated;
            
            // Generate a more advanced random sequence
            srand(time(0));
            string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
            for (int i = 0; i < 8; ++i) {
                generated += characters[rand() % characters.length()];
            }
            
            // Mix name and surname with the generated sequence
            newPassword = name.substr(0, 2) + surname.substr(0, 2) + generated + name.substr(2) + surname.substr(2);
            inFile.close();
            return newPassword;
        }
    }
    inFile.close();
    return "No ID under that index";
}

int main()
{
    string ID;
    cout << "Enter the ID to find (e.g., ID003): ";
    cin >> ID;
    
    string pass = GeneratePassword(ID);
    if (pass == "No ID under that index") {
        cout << pass << endl;
    } else {
        cout << "Generated Password: " << pass << endl;
    }
    return 0;
}