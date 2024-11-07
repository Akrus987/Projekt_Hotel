#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "klient.h"
using namespace std;

class Rezerwacja;

class Pokoj
{
    public:
        Pokoj();
        Pokoj(int nr, int os);
        int get_max(); //zwraca max liczbe osob
        int get_numer(); //zwraca nr pokoju
        string get_stan(); //zwraca stan
        void zmien_stan(string nowy_stan); //zmienia stan pokoju
        bool czy_zarezerwowany(int dzien, int miesiac) const;

        friend class Rezerwacja;
    private:
        int numer_; //nr pokoju
        int max_os_; //maksymalna liczba osob w pokoju
        string stan_; //"czysty", "zajety", "do posprzatania"
        vector<pair<pair<int, int>, Klient*>> rezerwacje_;  // rezerwacje pokoju
};
