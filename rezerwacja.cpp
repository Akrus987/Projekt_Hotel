#include "rezerwacja.h"

Rezerwacja::Rezerwacja(Data& d, Klient& k, Pokoj& p) : data(d), klient(k), pokoj(p), dzien_start(0), dzien_koniec(0) {}

void Rezerwacja::rezerwuj(int start, int koniec){
    for (int d = start; d <= koniec; d++){
        if (data.czy_zarezerwowany(d)){
            cout << "Dzien " << d << " jest juz zarezerwowany" << endl;
            return;
        }
    }

    for (int d = start; d <= koniec; d++){
        data.dodaj_rezerwacje(d);
    }
    
    dzien_start = start;
    dzine_koniec = koniec;

    pokoj.zmien_stan("zajety");
    cout << "Rezerwacja dla " << klient.get_imie() << " " << klient.get_nazwisko() << " od dnia " << dzien_start << " do " << dzien_koniec << " zostala dokonana" << endl;

}

void Rezerwacja::przedluz(int now_koniec) {
    for (int d = dzien_koniec + 1; d <= nowy_koniec; d++) {
        if (data.czy_zarezerwowany(d)) {
            cout << "Dzien " << d << " jest już zarezerwowany" << endl;
            return;
        }
    }
    for (int d = dzien_koniec + 1; d <= nowy_koniec; d++) {
        data.dodaj_rezerwacje(d);
    }
    dzien_koniec = nowy_koniec;
    cout << "Rezerwacja została przedłużona do dnia " << dzien_koniec << endl;
}

void Rezerwacja::skroc(int nowy_koniec) {
    if (nowy_koniec < dzien_start || nowy_koniec >= dzien_koniec) {
        cout << "Niepoprawna operacja skracania" << endl;
        return;
    }
    for (int d = nowy_koniec + 1; d <= dzien_koniec; ++d) {
        data.usun_rezerwacje(d);
    }
    dzien_koniec = nowy_koniec;
    cout << "Rezerwacja została skrócona do dnia " << dzien_koniec << endl;
}

void Rezerwacja::odwolaj() {
    for (int d = dzien_start; d <= dzien_koniec; ++d) {
        data.usun_rezerwacje(d);
    }
    pokoj.zmien_stan("czysty");
    dzien_start = dzien_koniec = 0;
    cout << "Rezerwacja została odwołana" << endl;
}
