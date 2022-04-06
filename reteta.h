#pragma once
#include "repository.h"
#include <vector>
#include "Observer.h"
using std::vector;

// Clasa pentru a caracteriza obiectele de tip Reteta 
class Reteta: public Observable
{
private:
	// Reteta contine o referinta catre repo si un vector unde vor fi stocate medicamentele de pe reteta
	// ar trebui sa punem const repo ul
	Repository& repo;
	vector<Medicament> reteta;
public:

	/*
	* Constructorul retetei
	* Date de intrare:-rep-de tip RepoMedicamente
	*/
	Reteta(Repository& rep) noexcept :repo{ rep } {

	}

	/*
	* Functie care goleste continutul unei retete
	*/
	void goleste_reteta();

	/*
	* Functie care adauga in reteta, pe baza denumirii, un medicament
	* Date de intrare:-denumire-string
	* Date de iesire:-
	*				  (daca medicamentul a fost adaugat)
	*				 - ridica exceptie de tip RepoException daca medicamentul cu denumirea respectiva nu se afla in lista
	*/
	void adauga_reteta(const string& denumire);

	/*
	* Functie care returneaza numarul de medicamente de pe reteta
	* Date de iesire:-lungimea listei-int
	*/
	int dimensiune_reteta() const noexcept;

	/*
	* Functie care returneaza reteta cu medicamente
	* Date de iesire:-returneaza lista cu medicamente de pe reteta
	*/
	const vector<Medicament>& get_reteta() const noexcept;

	/*
	* Functie care adauga random un numar nr de medicamente existente in lista (repo), pe reteta
	* Sterge tot ce era inainte pe reteta
	* Date de intrare:-nr-int
	*/
	void genereaza_reteta(int nr);

	/*
	* Functie care exporta medicamentele din reteta intr-un fisier CSV.
	* Date de intrare:-nume_fis-string
	*/
	void exporta(const string& nume_fis) const;

	// returneaza ce se afla in repo
	const vector<Medicament>& get_all() {
		return repo.get_all();
	}
};
