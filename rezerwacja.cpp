#include "rezerwacja.h"
using namespace std;

Rezerwacja::Rezerwacja(Data& d, Klient& k, Pokoj& p, int start_dzien, int start_miesiac, int koniec_dzien, int koniec_miesiac, int rok)
    : data(d), klient(k), pokoj(p), dzien_start(start_dzien), miesiac_start(start_miesiac), dzien_koniec(koniec_dzien), miesiac_koniec(koniec_miesiac), rok_rezerwacji(rok) {}

void Rezerwacja::rezerwuj(int start_dzien, int start_miesiac, int koniec_dzien, int koniec_miesiac, int rok) {
    for (int m = start_miesiac; m <= koniec_miesiac; m++) { // petla po miesiacach i sprawdza czy dana data jest zarezerwowana
        int dzien_start = (m == start_miesiac) ? start_dzien : 1;        // jesli obecny miesiac(m) jest taki sam jak start_miesiac to dzien_start ustawiany jet na start_dzien, w innym wypadku na 1
        int dzien_koniec = (m == koniec_miesiac) ? koniec_dzien : 31;    // jesli obecny miesiac(m) jest taki sam jak koniec_miesiac to dzien_koniec ustawiany jet na koniec_dzien, w innym wypadku na 31

        for (int d = dzien_start; d <= dzien_koniec; d++) {
            if (data.czy_zarezerwowany(d, m, pokoj)) {
                cout << "Dzien " << d << "/" << m << " jest już zarezerwowany" << endl;
                return;
            }
        }
    }

    for (int m = start_miesiac; m <= koniec_miesiac; m++) {
        int dzien_start = (m == start_miesiac) ? start_dzien : 1;
        int dzien_koniec = (m == koniec_miesiac) ? koniec_dzien : 31; 

        for (int d = dzien_start; d <= dzien_koniec; d++) {
            data.dodaj_rezerwacje(d, m, &klient, pokoj);
        }
    }

    dzien_start = start_dzien;
    miesiac_start = start_miesiac;
    dzien_koniec = koniec_dzien;
    miesiac_koniec = koniec_miesiac;
    rok_rezerwacji = rok;
    
    pokoj.zmien_stan("zajety");
    cout << "Rezerwacja dla " << klient.get_imie() << " " << klient.get_nazwisko() << " od " << dzien_start << "/" << miesiac_start
         << " do " << dzien_koniec << "/" << miesiac_koniec << " została dokonana" << endl;
}

void Rezerwacja::przedluz(int nowy_koniec_dzien, int nowy_koniec_miesiac) {
        if (nowy_koniec_miesiac < miesiac_koniec || (nowy_koniec_miesiac == miesiac_koniec && nowy_koniec_dzien <= dzien_koniec)) {
            cout << "Nowy koniec rezerwacji musi byc pozniej niz obecny koniec." << endl;
            return;
        }

        for (int m = miesiac_koniec; m <= nowy_koniec_miesiac; m++) { // sprawdza czy nowa data jest dostepna
            int dzien_start = (m == miesiac_koniec) ? dzien_koniec + 1 : 1;
            int dzien_koniec = (m == nowy_koniec_miesiac) ? nowy_koniec_dzien : 31;

            for (int d = dzien_start; d <= dzien_koniec; d++) {
                if (data.czy_zarezerwowany(d, m, pokoj)) {
                    cout << "Dzien " << d << "/" << m << " jest juz zarezerwowany!" << endl;
                    return;
                }
            }
        }

        for (int m = miesiac_koniec; m <= nowy_koniec_miesiac; m++) { // przedluza rezerwacje dodajac nowe dni
            int dzien_start = (m == miesiac_koniec) ? dzien_koniec + 1 : 1;
            int dzien_koniec = (m == nowy_koniec_miesiac) ? nowy_koniec_dzien : 31;

            for (int d = dzien_start; d <= dzien_koniec; d++) {
                data.dodaj_rezerwacje(d, m, &klient, pokoj);
            }
        }

        dzien_koniec = nowy_koniec_dzien;
        miesiac_koniec = nowy_koniec_miesiac;

        cout << "Rezerwacja zostala przedluzona do " << dzien_koniec << "/" << miesiac_koniec << endl;
    }

void Rezerwacja::skroc(int nowy_koniec_dzien, int nowy_koniec_miesiac) {
    if (nowy_koniec_miesiac < miesiac_start || (nowy_koniec_miesiac == miesiac_start && nowy_koniec_dzien < dzien_start)) {
        cout << "Nowy koniec rezerwacji nie moze byc wczesniejszy niz poczatek rezerwacji!" << endl;
        return;
    }

    if (nowy_koniec_miesiac > miesiac_koniec || (nowy_koniec_miesiac == miesiac_koniec && nowy_koniec_dzien >= dzien_koniec)) {
        cout << "Nowy koniec rezerwacji musi byc przed obecnym koncem rezerwacji!" << endl;
        return;
    }

    for (int m = nowy_koniec_miesiac + 1; m <= miesiac_koniec; ++m) {
        for (int d = 1; d <= 31; ++d) {
            data.usun_rezerwacje(d, m, &klient, pokoj);
        }
    }

    for (int d = nowy_koniec_dzien + 1; d <= dzien_koniec; ++d) {
        data.usun_rezerwacje(d, miesiac_koniec, &klient, pokoj);
    }
    dzien_koniec = nowy_koniec_dzien;
    miesiac_koniec = nowy_koniec_miesiac;

    cout << "Rezerwacja zostala skrocona do " << dzien_koniec << "/" << miesiac_koniec << endl;
}

void Rezerwacja::odwolaj(int start_dzien, int start_miesiac, int koniec_dzien, int koniec_miesiac, int rok) {
    for (int m = miesiac_start; m <= miesiac_koniec; m++) {
        int dzien_start = (m == miesiac_start) ? start_dzien : 1;
        int dzien_koniec = (m == miesiac_koniec) ? koniec_dzien : 31; 

        for (int d = dzien_start; d <= dzien_koniec; ++d) {
            data.usun_rezerwacje(d, m, &klient, pokoj);
        }
    }

    pokoj.zmien_stan("do posprzatania");
    dzien_start = dzien_koniec = 0;
    miesiac_start = miesiac_koniec = 0;
    cout << "Rezerwacja została odwołana" << endl;
}
