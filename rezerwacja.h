#pragma once
#include "data.h"
#include "pokoj.h"
#include "klient.h"

class Rezerwacja{
    private:
        Data& data;
        Klient& klient;
        Pokoj& pokoj;
        int dzien_start; // pierwszy dzien rezerwacji
        int dzien_koniec; // ostatni dzien rezerwacji
        int miesiac_start; // miesiac w ktorym rozpoczela sie rezerwacja
        int miesiac_koniec; // miesiac w ktorym zakonczyla sie rezerwacja
        int rok_rezerwacji; // rok w ktorym jest rezerwacja

    public:
        Rezerwacja(Data& d, Klient& k, Pokoj& , int start_dzien, int start_miesiac, int koniec_dzien, int koniec_miesiac, int rok_rezerwacji);
        void rezerwuj(int start_dzien, int start_miesiac, int koniec_dzien, int koniec_miesiac, int rok); // rezerwuje pobyt od start do koniec
        void przedluz(int nowy_koniec_dzien, int nowy_koniec_miesiac);  //przedluza pobyt do dnia nowy_koniec
        void skroc(int nowy_koniec_dzien, int nowy_koniec_miesiac);    //skraca pobyt do dnia nowy_koniec
        void odwolaj();     //anuluje pobyt

};


