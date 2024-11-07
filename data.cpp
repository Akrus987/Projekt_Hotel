#include "data.h"
using namespace std;

void Data::dodaj_rezerwacje(int dzien, int miesiac, Klient* klient, Pokoj& pokoj) {
    zarezerwowane_dni.push_back({{dzien, miesiac}, {klient, &pokoj}});
}

void Data::usun_rezerwacje(int dzien, int miesiac, Klient* klient, Pokoj& pokoj) {
    for (auto i = zarezerwowane_dni.begin(); i != zarezerwowane_dni.end(); i++) {    // Przeszukaj wszystkie rezerwacje
        if (i->first.first == dzien && i->first.second == miesiac && i->second.first == klient && i->second.second == &pokoj) { //Sprawdź, czy rezerwacja pasuje do podanych danych 
            zarezerwowane_dni.erase(i);
            break; // Zakończ pętlę, ponieważ rezerwacja została znaleziona
        }
    }
}

bool Data::czy_zarezerwowany(int dzien, int miesiac, Pokoj& pokoj) const {
    for (const auto& dni : zarezerwowane_dni) {
        if (dni.first.first == dzien && dni.first.second == miesiac && dni.second.second == &pokoj) {
            return true;  // Pokój jest zarezerwowany na dany dzień i miesiąc
        }
    }
    return false;  // Pokój jest wolny
}

void Data::get_zarezerwowane() const {
    cout << "Zarezerwowane dni: ";
    for (const auto& dni : zarezerwowane_dni) {
        cout << dni.first.first << "/" << dni.first.second << " (Klient: " << dni.second.first->get_imie() << " " << dni.second.first->get_nazwisko() << ", Pokój nr: " 
        << dni.second.second->get_numer() << ") ";
    }
    cout << endl;
}
