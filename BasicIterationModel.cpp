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
    string ID="0", name, surname, age, type="g";
    for (const auto& row : data) 
    {
        if (row[5] == "x")
        {
            ID = row[0];
            break;
        }
    }
    if (ID == "0") 
    {
        cout << "No more space for new users." << endl;
        return;
    }
    updateGuest(data, passwords, ID);
    
}

string getType(const vector<vector<string>>& data, const string& ID) {
    for (const auto& row : data) {
        if (row[0] == ID) {
            return row[5];
        }
    }
    return "x";
}

bool isValidDate(const string& date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (!isdigit(date[i])) {
            return false;
        }
    }
    return true;
}

void bookRoom(vector<vector<string>>& data, vector<vector<string>>& rooms, const string& ID) {
    string IDChecked = FormatID(ID);
    for (auto& row : data) {
        if (row[0] == IDChecked) {
            int people;
            cout << "Enter the number of people (1-5): ";
            cin >> people;
            while (people <= 0 && people > 5) {
                cout << "Invalid number of people." << endl;
                cout << "Enter the number of people: ";
                cin >> people;
            }
            stringstream ss;
            ss << people;
            string str_people = ss.str();

            string startDate, endDate;
            cout << "Enter the start date (YYYY-MM-DD): ";
            cin >> startDate;
            while (!isValidDate(startDate)) {
                cout << "Invalid date format. It must be in the format YYYY-MM-DD." << endl;
                cout << "Enter the start date (YYYY-MM-DD): ";
                cin >> startDate;
            }
            cout << "Enter the end date (YYYY-MM-DD): ";
            cin >> endDate;
            while (!isValidDate(endDate)) {
                cout << "Invalid date format. It must be in the format YYYY-MM-DD." << endl;
                cout << "Enter the end date (YYYY-MM-DD): ";
                cin >> endDate;
            }

            bool roomFound = false;
            for (auto& room : rooms) {
                if (room[1] == str_people && room[3] == "nie") {
                    row[4] = room[1];
                    cout << "Room " << room[1] << " has been successfully booked." << endl;
                    roomFound = true;
                    room[3] = "zarezerwowany";
                    room[6] = startDate;
                    room[7] = endDate;
                    room[8] = row[1];
                    room[9] = row[2];
                    break;
                }
            }

            if (!roomFound) {
                cout << "No available room found for " << people << " people from " << startDate << " to " << endDate << "." << endl;
            }
            return;
        }
    }
    cout << "No ID under that index" << endl;
}