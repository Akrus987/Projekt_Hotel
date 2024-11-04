#pragma once
#include "data.h"
#include "pokoj.h"
#include "klient.h"
#include <iostream>

class Rezerwacja{
    private:
        Data& data;
        Klient& klient;
        Pokoj& pokoj;
        int dzien_start; // pierwszy dzien rezerwacji
        int dzien_koniec; // ostatni dzien rezerwacji

    public:
        Rezerwacja(Data& d, Klient& k, Pokoj& p);
        void rezerwuj(int start, int koniec); // rezerwuje pobyt od start do koniec
        void przedluz(int nowy_koniec);  //przedluza pobyt do dnia nowy_koniec
        void skroc(int nowy_koniec);    //skraca pobyt do dnia nowy_koniec
        void odwolaj();     //anuluje pobyt

};