#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pokoj
{
    public:
        Pokoj();
        Pokoj(int nr, int os);
        int get_max(); //zwraca max liczbe osob
        int get_numer(); //zwraca nr pokoju
        string get_stan(); //zwraca stan
        void zmien_stan(string nowy_stan); //zmienia stan pokoju
    private:
        int numer_; //nr pokoju
        int max_os_; //maksymalna liczba osob w pokoju
        string stan_; //"czysty", "zajety", "do posprzatania"
};
