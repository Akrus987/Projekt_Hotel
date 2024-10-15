1. Co potrzeba
Rodzaje użytkowników: Admin, Gość hotelowy, Gość zewnętrzny (osoba chcąca zarezerwować pokój).
Funkcjonalności:
Logowanie (role: admin, gość hotelowy, gość zewnętrzny)
Zarządzanie pokojami (widoczność stanu, edycja dla admina)
Rezerwacje (goście mogą rezerwować, przedłużać, anulować)
Dane o gościach (informacje osobiste, przypisanie do pokoju, metoda płatności)
GUI: możliwość wyboru opcji (podgląd, edycja, rezerwacja)



2. Struktury
Klasy:
User: bazowa klasa dla kont użytkowników (Admin, Gość hotelowy, Gość)
Room: zawiera informacje o pokojach (numer, status, daty rezerwacji, czystość, gość przypisany do pokoju)
Reservation: klasa przechowująca dane o rezerwacjach (gość, pokój, daty)
GuestInfo: zawiera dane gości (imię, nazwisko, wiek, metoda płatności)
Hotel: centralna klasa zarządzająca pokojami, rezerwacjami i gośćmi


3. Baza danych
Zamiast SQL, dane będą przechowywane w plikach tekstowych. Trzeba znaleźć sposób odczytania i zarządzania tymi plikami. Trzeba zrobić to tak, by pliki były do siebie przypisane nawzajem, tak by nie zgubić lub wymieszać nazwisk. Moja propozycja:
fstream: całkiem prosta biblioteka do otwierania, odczytywania i zapisywania plików tekstowych
https://cpp0x.pl/kursy/Kurs-C++/Dodatkowe-materialy/Obsluga-plikow/305



4. Logowanie
Podstawowa weryfikacja na podstawie pliku z danymi użytkowników (users.dat).
Logowanie na różne konta w zależności od roli: admin, gość hotelowy, gość zewnętrzny.
Admin ma gotowe konto, gość hotelowy będzie otrzymywał konto z hasłem, zależne od imienia i wybranego pokoju, np:
Adam Walczak, pokój 302
login: AdamW302
hasło: XXXXXXX (losowo generowane 7 znaków)




5. Panel Administratora 
Widok listy pokoi: administrator widzi wszystkie pokoje, ich status (wolny, zajęty, posprzątany, itp.).
Możliwość edycji stanu pokoju (zmiana statusu: wolny/zajęty, aktualizacja rezerwacji).





6. Panel użytkownika/gościa
Po zalogowaniu, gość może przeglądać swoje rezerwacje i zarządzać nimi (przedłużyć, skrócić pobyt, anulować, dopłacić za anulowanie).
Proces rezerwacji: gość wybiera daty, uzupełnia dane osobowe, a system sprawdza dostępność pokoi i rezerwuje pokój w systemie.





7. Interfejs graficzny (GUI)
Można wykorzystać bibliotekę do GUI, np. SFML albo Qt, aby stworzyć interfejs okienkowy.
Proste okno logowania, a następnie różne panele w zależności od roli użytkownika (admin, gość).




8. Optymalizacje i zabezpieczenia
Dodać walidację wejścia (np. sprawdzanie poprawności daty rezerwacji, danych osobowych).
Zabezpieczenie plików przed nieautoryzowanym dostępem (np. szyfrowanie hasła w pliku z użytkownikami).
