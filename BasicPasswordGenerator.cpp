// BasicPasswordGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
using namespace std;
string GeneratePassword(string IDx)
{
    ifstream inFile;
    string x;
    string ID = IDx;
    string name;
    string surname;
    inFile.open("testing_ID.txt");
    
    while (inFile) 
    {
        inFile >> x;
        if (x == ID)
        {
            
            inFile >> name;
            inFile >> surname;
            string newPassword;
            stringstream stream;
            string generated;
            stream << rand() % 501;
            stream >> generated;
            newPassword = name + surname + generated;
           return newPassword;
        }
    }
    inFile.close();
    return "No ID under that index";
}

int main()
{
    string pass;
    pass = GeneratePassword("ID007");
    cout << pass;
    return 0;
}

