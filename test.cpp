#include <iostream>
#include "klient.h"
#include "pokoj.h"
#include "data.h"
#include "rezerwacja.h"

using namespace std;

int main() {
    Klient klient1("Anna", "Nowak");
    Klient klient2("Jan", "Kowalski");

    Pokoj pokoj1(101, 2);  
    Pokoj pokoj2(102, 3);  

    Data data;

    Rezerwacja rezerwacja1(data, klient1, pokoj1, 10, 5, 12, 5, 2024);
    Rezerwacja rezerwacja2(data, klient2, pokoj2, 13, 5, 15, 5, 2024);

    rezerwacja1.rezerwuj(10, 5, 12, 5, 2024);  // rezerwacja dla klienta1 od 10/5 do 12/5

    rezerwacja2.rezerwuj(11, 5, 13, 5, 2024);  // rezerwacja dla klienta2 od 11/5 do 13/5 (powinna sie nie udac)

    data.get_zarezerwowane();

    rezerwacja1.odwolaj(10, 5, 12, 5, 2024);

    data.get_zarezerwowane();

    rezerwacja2.skroc(12, 5);

    data.get_zarezerwowane();

    rezerwacja2.przedluz(17, 5);

    data.get_zarezerwowane();

    return 0;
}
