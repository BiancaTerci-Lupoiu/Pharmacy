#include<string>
#include"medicament.h"
#include<exception>
using std::string;
/*
* Clasa pentru a defini exceptiile aparute in repository
*/
class ValidException {
	//msg=mesajul furnizat de exceptie
	string msg;
public:
	//constructor
	ValidException(string m) :msg{ m } {
	}

	/*
	* returneaza mesajul exceptiei
	*/
	string get_mesaj() const;
};
/*
* Clasa pentru validarea entitatii "medicament"
*/
class Validator
{
public:
	/*
	* Functie care valideaza un medicament.
	* Date de intrare:-med- Medicament
	* Date de iesire:-
	*				 - ridica exceptie de tip ValidException daca medicamentul este invalid.
	*					(denumire-string vid | pret- <0 | producator-string vid | substanta-string vid)
	*/
	void valideaza(const Medicament& med);
};
