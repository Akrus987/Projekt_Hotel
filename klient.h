#pragma once
#include <iostream>
#include <string>
using namespace std;

class Rezerwacja;

class Klient
{
    public:
        Klient();
        Klient(string imie, string nazwisko);
        string get_imie();
        string get_nazwisko();

        friend class Rezerwacja;
    private:
        string imie_;
        string nazwisko_;
};
