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
            row.push_back(word);
        }
        data.push_back(row);
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

void displayData(const vector<vector<string>>& data, const string& ID) {
    for (const auto& row : data) {
        if (row[0] == ID) {
            cout << "ID is " << row[0] << "." << endl;
            cout << "The rest of info is: " << row[1] << " " << row[2] 
                 << ", age: " << row[3] << ", room: " << row[4] << endl;
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

void updateData(vector<vector<string>>& data, const string& ID) {
    for (auto& row : data) {
        if (row[0] == ID) {
            cout << "Enter new name: ";
            cin >> row[1];
            cout << "Enter new surname: ";
            cin >> row[2];
            cout << "Enter new age: ";
            cin >> row[3];
            cout << "Enter new room: ";
            cin >> row[4];
            return;
        }
    }
    cout << "No ID under that index" << endl;
}

int filename()
{
    vector<vector<string>> data = readData("testing_ID.txt");

    string ID;
    cout << "Enter the ID to display (e.g., ID003): ";
    cin >> ID;
    displayData(data, ID);
    char answer;
    cin >> answer;
    if (answer == 'y')
    {
        cout << "Enter the ID to update (e.g., ID003): ";
        cin >> ID;
        updateData(data, ID);
    }

    saveData("testing_ID.txt", data);

    return 0;
}