#ifndef BASIC_ITERATION_MODEL_H
#define BASIC_ITERATION_MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <windows.h>
#include "BasicPasswordGenerator.h"

using namespace std;

vector<vector<string>> readData(const string& filename, bool Passwordhashed = false);
void saveData(const string& dataFilename, const string& passwordFilename, const vector<vector<string>>& data, const vector<vector<string>>& passwordFile);
bool isValidName(const string& name);
bool isValidNumber(const string& number);
string FormatID(const string& input);
void displayData(const vector<vector<string>>& data, const string& ID);
void updateGuest(vector<vector<string>>& data, vector<vector<string>>& passwords, const string& ID);
string getUnhashedPassword(const vector<vector<string>>& passwords, const string& input);

#endif // BASIC_ITERATION_MODEL_H