#include "medicament.h"


Medicament::Medicament(string denumire, double pret, string producator, string substanta) :
	denumire{ denumire }, pret{ pret }, producator{ producator }, substanta{ substanta }{}

Medicament::Medicament(const Medicament& ot) : denumire{ ot.denumire }, pret{ ot.pret },
producator{ ot.producator }, substanta{ ot.substanta } {
	std::cout << "Copie\n";
}



bool Medicament::operator ==(const Medicament& med2) const noexcept {
	return this->denumire == med2.denumire;

}

Medicament& Medicament::operator =(const Medicament& med2) {
	this->denumire = med2.denumire;
	this->pret = med2.pret;
	this->producator = med2.producator;
	this->substanta = med2.substanta;
	return *this;
}


string Medicament::ToString() const {
	string str = "";
	str += "Denumire: " + denumire + " | pret: " + std::to_string(pret) + " | producator: " + producator + " | substanta activa: " + substanta;
	return str;

}