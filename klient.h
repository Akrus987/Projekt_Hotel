#pragma once
#include <iostream>
#include <string>
using namespace std;

class Klient
{
    public:
        Klient();
        Klient(string imie, string nazwisko);
        string get_imie();
        string get_nazwisko();
    private:
        string imie_;
        string nazwisko_;
};