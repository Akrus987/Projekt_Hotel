#include "data.h"

void Data::dodaj_rezerwacje(int dzien){
    if(!czy_zarezerwowany(dzien)) {
        zarezerwowane_dni.push_back(dzien); // push_back -> dodaje nowy element do konca vektora po ostatnim elemenci
    }
}

void Data::usun_rezerwacje(int dzien) {
    zarezerwowane_dni.erase(remove(zarezerwowane_dni.begin(), zarezerwowane_dni.end(), dzien), zarezerwowane_dni.end());
}

bool Data::czy_zarezerwowany(int dzien) const {
    return find(zarezerwowane_dni.begin(), zarezerwowane_dni.end(), dzien) != zarezerwowane_dni.end();
}

void Data::get_zarazerwowane() const {
    cout << "Zarezerwowane dni: ";
    for(int dzien : zarezerwowane_dni) {
        cout << dzien << " ";
    }
    cout << endl;
}
