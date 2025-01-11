#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

int main()
{
	ifstream inFile;
	inFile.open("testing_ID.txt");
	string x;
	string ID = "ID001";
	string name;
	string surname;
	int age = 0;
	int room;

	while (inFile)
	{
		inFile >> x;
		if (x == ID)
		{
			cout << "ID is " << x << "." << endl;
			inFile >> name;
			inFile >> surname;
			inFile >> age;
			inFile >> room;
			cout << "The rest of info is: " << name << " " << surname << ", age: " << age << ", room: " << room << endl;
			break;
		}
	}
	if (age==0) 
	{
	cout << "No ID under that index";
	}
	inFile.close();


}
//baza danych wektorowych -> dana jako wektor -> p?tla wyszukuje najbardziej zbli?on? odpowied? do wektora