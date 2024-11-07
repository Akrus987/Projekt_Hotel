#include "pokoj.h"
using namespace std;

Pokoj::Pokoj():numer_(0), max_os_(0), stan_("czysty"){} //konstruktor domyslny
Pokoj::Pokoj(int nr, int os):numer_(nr), max_os_(os), stan_("czysty"){}

int Pokoj::get_max()
{
    return max_os_;
}

int Pokoj::get_numer()
{
    return numer_;
}

void Pokoj::zmien_stan(string nowy_stan)
{
    if (nowy_stan=="czysty" or nowy_stan=="zajety" or nowy_stan=="do posprzatania")
    {
        stan_ = nowy_stan;
        return;
    }
    cout << "Niedozwolony stan" << endl;
}

string Pokoj::get_stan()
{
    return stan_;
}

bool Pokoj::czy_zarezerwowany(int dzien, int miesiac) const {
    for (const auto& rezerwacja : rezerwacje_) {
        if (rezerwacja.first.first == dzien && rezerwacja.first.second == miesiac) {
            return true;  // Pokój jest zarezerwowany
        }
    }
    return false;  // Pokój jest wolny
}
