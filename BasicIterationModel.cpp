// This program reads data from a file and stores it in a vector model.
// The vector model uses the first index [x][y], where x is the ID index and y is the data index.
// For example, x == 1 corresponds to ID001, y == 1 is the name, y == 2 is the surname, etc.
// The program allows for flexibility to add more data fields (y's) in the future.
// It also updates the changes by saving the whole vector back into the file.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include "BasicPasswordGenerator.h"

using namespace std;

vector<vector<string>> readData(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Unable to open file " << filename << endl;
        exit(1); // terminate with error
    }

    vector<vector<string>> data;
    string line, word;
    while (getline(inFile, line)) {
        stringstream ss(line);
        vector<string> row;
        while (ss >> word) {
            if (word.substr(0, 2) == "ID") {
                if (!row.empty()) {
                    data.push_back(row);
                    row.clear();
                }
            }
            row.push_back(word);
        }
        if (!row.empty()) {
            data.push_back(row);
        }
    }
    inFile.close();
    return data;
}

void saveData(const string& filename, const vector<vector<string>>& data) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Unable to open file " << filename << endl;
        exit(1); // terminate with error
    }
    for (const auto& row : data) {
        for (const auto& field : row) {
            outFile << field << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

bool isValidName(const string& name) {
    if (name.length() < 2 || name.length() > 25) {
        return false;
    }
    for (char c : name) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool isValidNumber(const string& number) {
    for (char c : number) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

string FormatID(const string& input)
{
    string ID;
    if (isdigit(input[0])) {
        ID = formatID(stoi(input));
    }
    else {
        ID = input;
    }
    return ID;
}

void displayData(const vector<vector<string>>& data, const string& ID) {
    for (const auto& row : data) {
        string IDChecked = FormatID(ID);
        if (row[0] == IDChecked) {
            cout << "ID is " << row[0] << "." << endl;
            cout << "The rest of info is: " << row[1] << " " << row[2] 
                 << ", age: " << row[3] << ", room: " << row[4];
            if (row.size() > 5) {
                cout << ", password: " << row[5];
            }
            cout << endl;
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

void updateGuest(vector<vector<string>>& data, const string& ID) {
    for (auto& row : data) {
        string IDChecked = FormatID(ID);
        if (row[0] == IDChecked) {
            string name, surname, age, room;
            cout << "Enter new name: ";
            cin >> name;
            if (!isValidName(name)) {
                cout << "Invalid name. It must be between 2 and 25 characters and contain only letters." << endl;
                return;
            }
            cout << "Enter new surname: ";
            cin >> surname;
            if (!isValidName(surname)) {
                cout << "Invalid surname. It must be between 2 and 25 characters and contain only letters." << endl;
                return;
            }
            cout << "Enter new age: ";
            cin >> age;
            if (!isValidNumber(age)) {
                cout << "Invalid age. It must contain only numbers." << endl;
                return;
            }
            cout << "Enter new room: ";
            cin >> room;
            if (!isValidNumber(room)) {
                cout << "Invalid room. It must contain only numbers." << endl;
                return;
            }
            row[1] = name;
            row[2] = surname;
            row[3] = age;
            row[4] = room;
            string newPassword = GeneratePassword(name, surname);
            if (row.size() > 5) {
                row[5] = newPassword; // Update the existing password
            } else {
                row.push_back(newPassword); // Add the new password
            }
            cout << "Generated Password: " << newPassword << endl;
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

string getUnhashedPassword(const vector<vector<string>>& data, const string& ID) {
    string IDChecked = FormatID(ID);
    for (const auto& row : data) {
        if (row[0] == IDChecked) {
            if (row.size() > 5) {
                return UnhashPassword(row[5]);
            } else {
                throw runtime_error("No password found for the given ID.");
            }
        }
    }
    throw runtime_error("No ID under that index.");
}

int main()
{

    vector<vector<string>> MainIdFile = readData("testing_ID.txt");
    vector<vector<string>> Passwords = readData("testing_Passwords.txt");
    
    string input;
    cout << "Enter the ID to display (e.g., ID003 or 3): ";
    cin >> input;

    displayData(MainIdFile, input);

    char answer;
    cout << "Do you want to update an ID? (y/n): ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
    {
        cout << "Enter the ID to update (e.g., ID003 or 3): ";
        cin >> input;
        updateGuest(MainIdFile, input);
        saveData("testing_ID.txt", MainIdFile);
    }
    
    return 0;
}