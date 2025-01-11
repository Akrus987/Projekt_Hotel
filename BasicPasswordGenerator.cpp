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
            for (int i = 0; i < 8; ++i) {
                char randomChar = 'A' + rand() % 26;
                generated += randomChar;
            }
            
            newPassword = name + surname + generated;
            inFile.close();
            return newPassword;
        }
    }
    inFile.close();
    return "";
}

int main()
{
    string ID;
    cout << "Enter the ID to find: ";
    cin >> ID;
    
    string pass = GeneratePassword(ID);
    if (pass.empty()) {
        cout << "ID not found." << endl;
    } else {
        cout << "Generated Password: " << pass << endl;
    }
    return 0;
}