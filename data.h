#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Rezerwacja;

class Data{
    private:
        vector<int> zarezerwowane_dni; //jakie dni sa zarezerwowane
    public:
        void get_zarazerwowane() const; // zwraca zarezerwowane dni
        bool czy_zarezerwowany(int dzien) const; // sprawdza czy dzien jest zarezerwowany
        void dodaj_rezerwacje(int dzien); // dodaje dni do zarezerwowanych
        void usun_rezerwacje(int dzien); // usuwa dni z zarezerwowanych
        
        friend class Rezerwacja;
};
