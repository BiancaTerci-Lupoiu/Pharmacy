#pragma once
#include "service.h"

// tip de data UI
class UI {
private:
	// contine o referinta la un obiect de tip ServiceMedicamente
	ServiceMedicamente& srv;
public:

	/*
	* Constructorul UI-ului
	* Date de intrare:-serv-de tip ServiceMedicamente
	*/
	UI(ServiceMedicamente& serv) noexcept :srv{ serv } {

	}

	// functie ui de adaugare a unui medicament in lista
	void adauga_ui();

	// functie ui care afiseaza lista cu medicamente
	void afisare_medicamente();

	// functie care printeaza meniul
	void meniu();

	// functie care porneste aplicatia
	void start();

	// functie ui de modificare a unui medicament din lista
	void modifica_ui();

	// functie ui de cautare a unui medicament in lista
	void cauta_ui();

	// functie ui de stergere a unui medicament din lista
	void sterge_ui();

	// functie ui de filtrare dupa pret
	void filtru_pret();

	// functie ui de filtrare dupa substanta
	void filtru_substanta();

	// functie ui de sortare dupa denumire
	void sortare1();

	// functie ui de sortare dupa producator
	void sortare2();

	// functie ui de sortare dupa substanta si pret
	void sortare3();

	// functie ui de adaugare medicament pe reteta
	void adauga_reteta_ui();

	// functie ui de golire a retetei
	void goleste_reteta_ui();

	// funtie ui de afisare a retetei
	void afiseaza_reteta();

	// functie ui de generare a retetei
	void genereaza_reteta();

	// functie ui care afiseaza producatorii si numarul de medicamente de la fiecare producator
	void raport();

	// functue ui care exporta reteta intr-un fisier
	void exporta_reteta();

	// functue ui de undo
	void undo_ui();
};
