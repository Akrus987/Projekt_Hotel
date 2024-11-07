#pragma once
#include <vector>
#include <tuple>
#include <iostream>
using namespace std;

class Klient; 

class Data {
private:
    vector<pair<pair<int, int>, pair<Klient*, Pokoj*>>> zarezerwowane_dni; // przechowuje dane o rezerwacji vector<tuple> -> vektor przechowujacy 3 zmienne

public:
    void get_zarezerwowane() const; // zwraca wszystkie zarezerwowane dni z klientami
    bool czy_zarezerwowany(int dzien, int miesiac) const; // sprawdza czy dany dzien jest zarezerwowany przez klient
    void dodaj_rezerwacje(int dzien, int miesiac, Klient* klient); // dodaje rezerwacje
    void usun_rezerwacje(int dzien, int miesiac, Klient* klient); // usuwa rezerwacje
};
