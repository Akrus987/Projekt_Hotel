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
    vector<vector<string>> data = readData("data.txt");
    vector<vector<string>> passwordFile = readData("passwords.txt");
    int choice=0;
    bool run=1;
    cout << "Witaj w Hotelu!" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Utworz konto" << endl;
    cout << "2. Zaloguj sie" << endl;
    cout << "3. Wyjdz" << endl;
    cout << "--------------------------------" << endl;
    cin >> choice;
    while (run)
    {
            cout << "--------------------------------" << endl;
            cout << "1. Utworz konto" << endl;
            cout << "2. Zaloguj sie" << endl;
            cout << "3. Wyjdz" << endl;
            cout << "--------------------------------" << endl;
        switch (choice)
        {
            case 1:
            {
                break;   
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            default:
            {
                cout << "Niepoprawny wybor!" << endl;
                break;
            }
        }
    }
    return 0;
}
