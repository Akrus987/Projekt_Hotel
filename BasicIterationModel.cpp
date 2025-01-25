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

// Function declaration
string getUnhashedPassword(const vector<vector<string>>& passwords, const string& input);

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

        while (ss >> word) 
        {
            if (word.substr(0, 2) == "ID") 
            {
                if (!row.empty()) 
                {
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

void saveData(const string& dataFilename, const string& passwordFilename, const vector<vector<string>>& data, const vector<vector<string>>& passwordFile) {
    ofstream outFile(dataFilename);
    if (!outFile) {
        cerr << "Unable to open file " << dataFilename << endl;
        exit(1); // terminate with error
    }

    ofstream passFile(passwordFilename);
    if (!passFile) {
        cerr << "Unable to open file " << passwordFilename << endl;
        exit(1); // terminate with error
    }

    for (const auto& row : data) {
        for (const auto& field : row) {
            outFile << field << " ";
        }
        outFile << endl;
    }

    for (const auto& passRow : passwordFile) {
        passFile << passRow[0] << " " << passRow[1] << endl;
    }

    outFile.close();
    passFile.close();
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

void displayUser(const vector<vector<string>>& data, const string& ID ) {
    for (const auto& row : data) {
        if (row[0] == ID) 
        {
           cout << "Currently logged in as: " << row[1] << " " << row[2] << endl;
              return;
        }
    }
    cout << "No user with this ID." << endl;
}

bool isValidType(const string& type) {
    return type == "g" || type == "a" || type == "x";
}

void updateGuestAdmin(vector<vector<string>>& data, vector<vector<string>>& passwords, const string& ID) {
    string IDChecked = FormatID(ID);
    for (auto& row : data) {
        if (row[0] == IDChecked) {
            string name, surname, age, room, type;
            cout << "Enter the name: ";
            cin >> name;
            while (!isValidName(name)) {
                cout << "Invalid name. It must be between 2 and 25 characters and contain only letters." << endl;
                cout << "Enter the name: ";
                cin >> name;
            }
            cout << "Enter the surname: ";
            cin >> surname;
            while (!isValidName(surname)) {
                cout << "Invalid surname. It must be between 2 and 25 characters and contain only letters." << endl;
                cout << "Enter the surname: ";
                cin >> surname;
            }
            cout << "Enter the age: ";
            cin >> age;
            while (!isValidNumber(age)) {
                cout << "Invalid age. It must contain only numbers." << endl;
                cout << "Enter the age: ";
                cin >> age;
            }
            cout << "Enter the room: ";
            cin >> room;
            while (!isValidNumber(room)) {
                cout << "Invalid room. It must contain only numbers." << endl;
                cout << "Enter the room: ";
                cin >> room;
            }
            cout << "Enter the type (g - guest, a - admin, x - inactive): ";
            cin >> type;
            while (!isValidType(type)) {
                cout << "Invalid type. It must be g, a, or x." << endl;
                cout << "Enter the type (g - guest, a - admin, x - inactive): ";
                cin >> type;
            }

            row[1] = name;
            row[2] = surname;
            row[3] = age;
            row[4] = room;
            row[5] = type;
            string Pass = GeneratePassword(name, surname);
            string Password = HashPassword(Pass);
            bool passwordUpdated = false;
            for (auto& passRow : passwords) {
                if (passRow[0] == IDChecked) {
                    passRow[1] = Password;
                    passwordUpdated = true;
                    break;
                }
            }
            if (!passwordUpdated) {
                passwords.push_back({IDChecked, Password});
            }
            cout << "Generated Password: " << Pass << endl;
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

void updateGuest(vector<vector<string>>& data, vector<vector<string>>& passwords, const string& ID) {
    string IDChecked = FormatID(ID);
    for (auto& row : data) {
        if (row[0] == IDChecked) {
            string name, surname, age;
            cout << "Enter the name: ";
            cin >> name;
            while (!isValidName(name)) {
                cout << "Invalid name. It must be between 2 and 25 characters and contain only letters." << endl;
                cout << "Enter the name: ";
                cin >> name;
            }
            cout << "Enter the surname: ";
            cin >> surname;
            while (!isValidName(surname)) {
                cout << "Invalid surname. It must be between 2 and 25 characters and contain only letters." << endl;
                cout << "Enter the surname: ";
                cin >> surname;
            }
            cout << "Enter the age: ";
            cin >> age;
            while (!isValidNumber(age)) {
                cout << "Invalid age. It must contain only numbers." << endl;
                cout << "Enter the age: ";
                cin >> age;
            }

            row[1] = name;
            row[2] = surname;
            row[3] = age;
            row[4] = "0";
            row[5] = "g";
            string Pass = GeneratePassword(name, surname);
            string Password = HashPassword(Pass);
            bool passwordUpdated = false;
            for (auto& passRow : passwords) {
                if (passRow[0] == IDChecked) {
                    passRow[1] = Password;
                    passwordUpdated = true;
                    break;
                }
            }
            if (!passwordUpdated) {
                passwords.push_back({IDChecked, Password});
            }
            cout << "Generated Password: " << Pass << endl;
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

string getUnhashedPassword(const vector<vector<string>>& passwords, const string& input) 
{
string ID = FormatID(input);
    for (const auto& row : passwords) 
    {
        if (row[0] == ID) 
        {
            if (row.size() > 1)
            {
                return UnhashPassword(row[1]);
            } 
            else 
            {
                throw runtime_error("No password found for the given ID.");
            }
        }
    }
    throw runtime_error("No ID under that index.");
}

string getID(const vector<vector<string>>& data, const string& imie, const string& nazwisko) {
    for (const auto& row : data) {
        if (row[1] == imie && row[2] == nazwisko) {
            return row[0];
        }
    }
    return "ID000";
}

string login(const vector<vector<string>>& passwords, const string& ID, const string& password) {
        if (ID == "ID000") {
            cout << "No user with this name and surname." << endl;
            return "NULL";
        }
        for (const auto& passRow : passwords) {
            if (passRow[0] == ID) {
                if (UnhashPassword(passRow[1]) == password) {
                    cout << "Login successful." << endl;
                    return ID;
                }
                else {
                    cout <<  "Incorrect password." << endl;
                    return "NULL";
                }
            }
        }
        cout << "No password found for the given ID." << endl;
        return "NULL";
}

void new_user(vector<vector<string>>& data, vector<vector<string>>& passwords) {
    string ID, name, surname, age, type="g";
    for (const auto& row : data) 
    {
        if (row[5] == "x")
        {
            ID = row[0];
            break;
        }
    }

    cout << "Enter the name: ";
    cin >> name;
    while (!isValidName(name)) {
        cout << "Invalid name. It must be between 2 and 25 characters and contain only letters." << endl;
        cout << "Enter the name: ";
        cin >> name;
    }
    cout << "Enter the surname: ";
    cin >> surname;
    while (!isValidName(surname)) {
        cout << "Invalid surname. It must be between 2 and 25 characters and contain only letters." << endl;
        cout << "Enter the surname: ";
        cin >> surname;
    }
    cout << "Enter the age: ";
    cin >> age;
    while (!isValidNumber(age)) {
        cout << "Invalid age. It must contain only numbers." << endl;
        cout << "Enter the age: ";
        cin >> age;
    }

    string Pass = GeneratePassword(name, surname);
    string Password = HashPassword(Pass);
    data.push_back({ID, name, surname, age, "0", "g"});
    passwords.push_back({ID, Password});
    cout << "Generated Password: " << Pass << endl;
}

/*
int main() {
    cout<<HashPassword("JoSmZ1Vf0ml*hnith")<<endl;
    vector<vector<string>> MainIdFile = readData("testing.ID.txt");
    vector<vector<string>> Passwords = readData("testing_Passwords.txt");
/*
    string input;
    cout << "Enter the ID to display (e.g., ID003 or 3): ";
    cin >> input;

    displayData(MainIdFile, input);

    char answer;
    cout << "Do you want to update an ID? (y/n): ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        cout << "Enter the ID to update (e.g., ID003 or 3): ";
        cin >> input;
        updateGuest(MainIdFile, Passwords, input);
        saveData("testing_ID.txt", "testing_Passwords.txt", MainIdFile, Passwords);
    }

    string name, surname, password, current_user = "NULL";
    while (current_user == "NULL") {
        cout << "Enter the name: ";
        cin >> name;
        cout << "Enter the surname: ";
        cin >> surname;
        cout << "Enter the password: ";
        cin >> password;
        current_user = login(Passwords, getID(MainIdFile, name, surname), password); // logowanie zwraca ID zalogowanego uzytkownika
    }
    displayData(MainIdFile, current_user);

    char answer;
    cout << "Do you want to update your profile? (y/n): ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {

        updateGuestAdmin(MainIdFile, Passwords, current_user);
        saveData("testing_ID.txt", "testing_Passwords.txt", MainIdFile, Passwords);
    }
    //DaPr8MavNIpQriuszzybylski - nowe haslo
    return 0;
}*/