#include "klient.h"

Klient::Klient():imie_("Jan"), nazwisko_("Kowalski"){} //konstruktor domyslny
Klient::Klient(string imie, string nazwisko):imie_(imie), nazwisko_(nazwisko){}

string Klient::get_imie()
{
    return imie_;
}

string Klient::get_nazwisko()
{
    return nazwisko_;
}
