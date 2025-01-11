#ifndef BASIC_PASSWORD_GENERATOR_H
#define BASIC_PASSWORD_GENERATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

string formatID(int num) {
    stringstream ss;
    ss << "ID" << setw(3) << setfill('0') << num;
    return ss.str();
}

string GeneratePassword(const string& name, const string& surname)
{
    string newPassword, generated;
    
    // Generate a more advanced random sequence
    srand(time(0));
    string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
    for (int i = 0; i < 8; ++i) {
        generated += characters[rand() % characters.length()];
    }
    
    // Mix name and surname with the generated sequence
    newPassword = name.substr(0, 2) + surname.substr(0, 2) + generated + name.substr(2) + surname.substr(2);
    return newPassword;
}

#endif // BASIC_PASSWORD_GENERATOR_H