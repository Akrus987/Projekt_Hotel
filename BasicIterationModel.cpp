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

void listactiveID(const vector<vector<string>>& data){
    for (const auto& row : data) {
        if (row[5] != "x") {
            for(int i = 0; i < row.size(); i++)
            {
                cout << row[i] << " ";
            }
            cout << endl;
        }
        else if (row[5] != "g")
        {
            for(int i = 0; i < row.size(); i++)
            {
                cout << row[i] << " ";
            }
            cout << endl;
        
    }
    cout << endl;
}}

bool isDateValid( std::vector<int> time ) {
    if( time[0] < 2024 || time[0] > 2030 ) return false; //year
    if( time[1]> 12) return false; //month
    if( time[2]> 31 ) return false; //day
    if( time[2] == 31 && ( time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11 ) ) return false; //30 days in Apr, Jun, Sen, Nov
    if( time[1] == 2) {
      if( time[2] > 29 ) return false;
      if( time[2] == 29 && ( ( time[0]%100 )%4 != 0) ) return false;
    } //Feb
    return true;
    }

void updateReservation(vector<vector<string>>& reservations, const string& ID) {
    string IDChecked = FormatID(ID);
    for (auto& row : reservations) {
        if (row[0] == IDChecked) {
            
            string room;
            cout << "Choose a room to make a reservation with: ";
            cin >> room;
            row[1] = room;
            cout << "Is there a revervation to be made? y/n" << endl;
            string ongoing;
            cin >> ongoing;
            while (ongoing != "y" && ongoing != "n") {
                cout << "Invalid input. Please enter yes or no." << endl;
                cin >> ongoing;
            }
            if(ongoing == "y")
            {
                ongoing = "zajety";
                row[3] = ongoing;
                cout << "When does the reservation start? YYYY MM DD  ";
                vector<int> start = {0,0,0};
                int day, month, year;
                cin>> day >> month >> year;
                /*if(isDateValid(start) == false)
                {
                    cout << "Invalid date." << endl;
                    return;
                }*/
                start[0] = year;
                start[1] = month;
                start[2] = day;
                
                cout << "When does the reservation end? YYYY MM DD ";
                vector<int> end = {0,0,0};
                int day_2;
                int month_2;
                int year_2;
                cin>> day_2 >> month_2 >> year_2;
                /*if(isDateValid(end) == false)
                {
                    cout << "Invalid date." << endl;
                    return;
                }*/
                end[0] = year_2;
                end[1] = month_2;
                end[2] = day_2;

                cout << "Who is the reservation for? ";
                string name;
                cin >> name;
                cout << "Is the room clean? y/n" << endl;
                string clean;
                cin >> clean;
                if(clean == "n")
                {
                    clean = "brudny";
                }
                else if(clean == "y")
                {
                    clean = "czysty";
                }
                row[4] = "zarezerwowany";
                row[5] = clean;
                row[6] = "(" + to_string(start[0]) + "/" + to_string(start[1]) + "/" + to_string(start[2]) + ")";
                row[7] = "(" + to_string(end[0]) + "/" + to_string(end[1]) + "/" + to_string(end[2]) + ")";
                row[8] = name;
                cout << "Reservation updated." << endl;
                return;
            }
            
            else if (ongoing == "n")
            {
                row[3] = "wolny";
                cout << "Reservation updated." << endl;
                row[6] = "0";
                row[7] = "0";
                row[8] = "0";
                return;
            }
            
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

