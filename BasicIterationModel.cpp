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
#include <ctime>
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


vector<int> convertDateStringToIntVector(const string& date) {
    vector<int> dateVector(3);
    stringstream ss(date);
    char delimiter;

    ss >> dateVector[0] >> delimiter >> dateVector[1] >> delimiter >> dateVector[2];

    return dateVector;
}

bool isDateGood( std::vector<int> time ) {
    if( time[1]> 12) return false; //miesiac
    if( time[2]> 31 ) return false; //dzien
    if( time[2] == 31 && ( time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11 ) ) return false; //30 dzni in Apr, Jun, Sen, Nov
    if( time[1] == 2) {
      if( time[2] > 29 ) return false;
      if( time[2] == 29 && ( ( time[0]%100 )%4 != 0) ) return false;
    } //luty
    return true;
    }
//poprawnosc formatu daty
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
    if (isDateGood(convertDateStringToIntVector(date))) {
        return true;
    }
    else {
        return false;
    }
}



// funkcja sprawdza czy data jest przynajmniej jeden tydzien w przyszlosci
bool isDateCorrect(const string& date) {
    if (!isValidDate(date)) {
        cout << "Invalid date format. It must be in the format YYYY-MM-DD." << endl;
        return false;
    }

    // aktualna data
    time_t t = time(nullptr);
    tm* currentTime = localtime(&t);

    // aktualna data + tydzien
    const int tydzien = 7 * 24 * 60 * 60;
    t += tydzien;
    tm* futureTime = localtime(&t);

    int futureYear = futureTime->tm_year + 1900;
    int futureMonth = futureTime->tm_mon + 1;
    int futureDay = futureTime->tm_mday;

    
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    // porownanie dat
    if (year < futureYear) {
        return false;
    } else if (year == futureYear) {
        if (month < futureMonth) {
            return false;
        } else if (month == futureMonth) {
            if (day < futureDay) {
                return false;
            }
        }
    }

    return true;
}

bool isDateGreater(const string& date1, const string& date2) {
    // czy daty sa poprawne
    if (!isValidDate(date1) || !isValidDate(date2)) {
        cout << "Invalid date format. It must be in the format YYYY-MM-DD." << endl;
        return false;
    }

    //data 1
    int year1, month1, day1;
    sscanf(date1.c_str(), "%d-%d-%d", &year1, &month1, &day1);

    //data 2
    int year2, month2, day2;
    sscanf(date2.c_str(), "%d-%d-%d", &year2, &month2, &day2);

    // poriwnanie dat
    if (year1 > year2) {
        return true;
    } 
    else if (year1 == year2) {
        if (month1 > month2) {
            return true;
        } else if (month1 == month2) {
            if (day1 > day2) {
                return true;
            }
        }
    }

    return false;
}

void updateReservation(vector<vector<string>>& reservations, const string& ID) {
    string IDChecked = FormatID(ID);
    for (auto& row : reservations) {
        if (row[0] == IDChecked) {
            string room;
            cout << "Choose a room to make a reservation with: ";
            cin >> room;
            row[1] = room;

            cout << "Is there a reservation to be made? y/n" << endl;
            string ongoing;
            cin >> ongoing;
            while (ongoing != "y" && ongoing != "n") {
                cout << "Invalid input. Please enter y or n." << endl;
                cin >> ongoing;
            }

            if (ongoing == "y") {
                ongoing = "zajety";
                row[3] = ongoing;

                string start, end, name, clean;
                cout << "Enter the start date (YYYY-MM-DD): ";
                cin >> start;
                while (!isValidDate(start)) {
                    cout << "Invalid date format. It must be in the format YYYY-MM-DD." << endl;
                    cout << "Enter the start date (YYYY-MM-DD): ";
                    cin >> start;
                }

                cout << "Enter the end date (YYYY-MM-DD): ";
                cin >> end;
                while (!isValidDate(end)) {
                    cout << "Invalid date format. It must be in the format YYYY-MM-DD." << endl;
                    cout << "Enter the end date (YYYY-MM-DD): ";
                    cin >> end;
                }

                cout << "Who is the reservation for? ";
                cin >> name;

                cout << "Is the room clean? y/n" << endl;
                cin >> clean;
                while (clean != "y" && clean != "n") {
                    cout << "Invalid input. Please enter y or n." << endl;
                    cin >> clean;
                }
                clean = (clean == "y") ? "czysty" : "brudny";

                row[4] = "zarezerwowany";
                row[5] = clean;
                row[6] = start;
                row[7] = end;
                row[8] = name;
                cout << "Reservation updated." << endl;
                return;
            } else if (ongoing == "n") {
                row[3] = "wolny";
                row[4] = "nie";
                row[5] = "nie";
                row[6] = "0";
                row[7] = "0";
                row[8] = "0";
                cout << "Reservation canceled." << endl;
                return;
            }
        }
    }
    cout << "No ID under that index" << endl;
}

void bookRoom(vector<vector<string>>& data, vector<vector<string>>& rooms, const string& ID) {
    string IDChecked = FormatID(ID);
    for (auto& row : data) {
        if (row[0] == IDChecked) {
            if (row[4] != "0") {
                cout << "You already have a room booked." << endl;
                return;
            }
            int people;
            cout << "Enter the number of people (1-5): ";
            cin >> people;
            while (people <= 0 || people > 5) {
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
            while (!isDateCorrect(startDate)) {
                cout << "Date must be at least 7 days in the future" << endl;
                cout << "Enter the start date (YYYY-MM-DD): ";
                cin >> startDate;
            }
            cout << "Enter the end date (YYYY-MM-DD): ";
            cin >> endDate;
            while (!isDateGreater(endDate, startDate)) {
                cout << "Date must be grater than start date." << endl;
                cout << "Enter the end date (YYYY-MM-DD): ";
                cin >> endDate;
            }

            bool roomFound = false;
            for (auto& room : rooms) {
                if (room[2] == str_people && room[4] == "nie") {
                    row[4] = room[1];
                    cout << "Room " << room[1] << " has been successfully booked." << endl;
                    roomFound = true;
                    room[4] = "zarezerwowany";
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

int checkdays(const string& start, const string& end);
int calculateprice(vector<vector<string>>& reservations, const int& nrpokoju);


void checkReservation(vector<vector<string>>& data, vector<vector<string>>& reservations, string& ID) {
    string IDChecked = FormatID(ID);
    string room = "0";
    for (const auto& row : data) {
        if (row[0] == IDChecked) {
            room = row[4];
            break;
        }
    }

    for (auto& row : reservations) {
        if (row[1] == room) {
            cout << "--------Info---------" << endl;
            cout << "Room number: " << row[1] << endl;
            cout << "Number of people: " << row[2] << endl;
            cout << "Start date: " << row[6] << endl;
            cout << "End date: " << row[7] << endl;
            cout << "Name: " << row[8] << " " << row[9] << endl;
            cout << "Current number of days staying: " << checkdays(row[6], row[7]) << endl;
            cout << "Current price for reservation: " << calculateprice(reservations, stoi(row[1])) << "$" << endl;
            cout << "---------------------" << endl;

            int choice;
            cout << "Would you like to:" << endl;
            cout << "1. Change reservation details" << endl;
            cout << "2. Cancel reservation" << endl;
            cout << "3. Go back" << endl;
            cout << "Choose option: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
                continue;
            }

            switch (choice) {
                case 1:
                {
                    cout << "Change reservation details" << endl;
                    updateReservation(reservations, ID);
                    break;
                }
                case 2:
                {
                    cout << "Cancel reservation" << endl;
                    row[3] = "wolny";
                    row[4] = "nie";
                    row[5] = "nie";
                    row[6] = "0";
                    row[7] = "0";
                    row[8] = "0";
                    row[9] = "0";
                    for (auto& guest : data) {
                        if (guest[0] == IDChecked) {
                            guest[4] = "0";
                            break;
                        }
                    }
                    cout << "Reservation canceled." << endl;
                    break;
                }
                case 3:
                {
                    cout << "Going back to the previous menu." << endl;
                    return;
                }
                default:
                {
                    cout << "Wrong choice!" << endl;
                    break;
                }
            }
            return;
        }
    }
    cout << "You do not have any booked rooms." << endl;
}
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

int checkdays(const string& start, const string& end) {
    vector<int> startDate = convertDateStringToIntVector(start);
    vector<int> endDate = convertDateStringToIntVector(end);

    int startYear = startDate[0];
    int startMonth = startDate[1];
    int startDay = startDate[2];

    int endYear = endDate[0];
    int endMonth = endDate[1];
    int endDay = endDate[2];

    int days = 0;

    // If the dates are in the same month and year
    if (startYear == endYear && startMonth == endMonth) {
        days = endDay - startDay;
    } else {
        // Calculate days remaining in the start month
        days += daysInMonth(startYear, startMonth) - startDay;

        // Add days for the months in between
        for (int month = startMonth + 1; month < endMonth; ++month) {
            days += daysInMonth(startYear, month);
        }

        // Add days for the end month
        days += endDay;

        // If the dates are in different years
        if (startYear != endYear) {
            // Add days for the months in the start year
            for (int month = startMonth + 1; month <= 12; ++month) {
                days += daysInMonth(startYear, month);
            }

            // Add days for the months in the end year
            for (int month = 1; month < endMonth; ++month) {
                days += daysInMonth(endYear, month);
            }

            // Add days for the years in between
            for (int year = startYear + 1; year < endYear; ++year) {
                days += isLeapYear(year) ? 366 : 365;
            }
        }
    }


    return days;
}

int calculateprice(vector<vector<string>>& reservations, const int& nrpokoju) {
    for (const auto& row : reservations) {
        if (stoi(row[1]) == nrpokoju) {
            int priceperday = 50 + (stoi(row[2]) - 1) * 25;
            int days = checkdays(row[6], row[7]);
            cout << "Price per day: " << priceperday << ", Days: " << days << endl; // Debugging
            return priceperday * days;
        }
    }
    cout << "No reservation found for this room." << endl;
    return 0; // Ensure that the function always returns a value
}