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

//Jakub i Michał
string formatID(int num) {
    stringstream ss;
    ss << "ID" << setw(3) << setfill('0') << num;
    return ss.str();
}
//Jakub i Michał
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

//Jakub i Michał
string HashPassword(const string& password) {
    string hashedPassword;
    for (char c : password) {
        hashedPassword += c + 3; // Shift each character by 3
    }
    return hashedPassword;
}
//Jakub i Michał
string UnhashPassword(const string& hashedPassword) {
    string unhashedPassword;
    for (char c : hashedPassword) {
        unhashedPassword += c - 3; // Shift each character back by 3
    }
    return unhashedPassword;
}
#endif // BASIC_PASSWORD_GENERATOR_H