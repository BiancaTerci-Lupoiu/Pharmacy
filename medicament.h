#pragma once
#include <string>
#include<iostream>
using std::string;
/*
* Clasa noua pentru a defini tipul de data Medicament
*/
class Medicament
{//identificator: denumire
private:
	// campurile unui Medicament
	string denumire;
	double pret;
	string producator;
	string substanta;

public:
	/*
	* returneaza pretul unui medicament
	*/
	double get_pret()const noexcept {
		return pret;
	}

	/*
	* returneaza denumirea unui medicament
	*/
	string get_denumire() const {
		return denumire;
	}

	/*
	* returneaza producatorul unui medicament
	*/
	string get_producator() const {
		return producator;
	}

	/*
	* returneaza substanta unui medicament
	*/
	string get_substanta() const {
		return substanta;
	}

	Medicament() = default;

	/*
	* Constructorul
	* Date de intrare:-denumire- de tip string
	*				  -pret- de tip double
	*				  -producator- de tip string
	*				  -substanta- de tip string
	*/
	Medicament(string denumire, double pret, string producator, string substanta);

	// constructorul de move->l-am setat cu default
	Medicament(Medicament&&) = default;

	//constructorul de copiere
	Medicament(const Medicament& ot);

	/*
	* Suprascrierea operatorului ==. Verifica daca 2 medicamente sunt egale (au aceeasi denumire)
	* returneaza:-true-daca sunt egale
	*			 -false-daca nu sunt egale
	*/
	bool operator==(const Medicament& med2) const noexcept;

	/*Operatorul =  inlocuieste continutul medicamentului curent cu continutul
	altui medicament (med2- care nu se modifica)*/
	Medicament& operator=(const Medicament& med2);

	/*
	* Face convert to string la campurile medicamentului. (Pentru a afisa mai frumos medicamentele)
	* returneaza stringul cu datele despre medicament.
	*/
	string ToString() const;

};