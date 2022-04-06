#pragma once
#include <vector>
#include<map>
#include "medicament.h"
#include "vectordinamic.h"
#include<exception>
using std::vector;
using std::map;


/*
* Clasa pentru a defini exceptiile aparute in repository
*/
class RepoException {
	//msg=mesajul furnizat de exceptie
	string msg;
public:
	//constructor
	RepoException(string m) :msg{ m } {
	}

	/*
	* returneaza mesajul exceptiei
	*/
	string get_mesaj() const;
};

class Repository
{
public:
	virtual void adauga(const Medicament& med) = 0;
	virtual const vector<Medicament>& get_all() = 0;
	virtual void modifica(const Medicament& med_modif) = 0;
	virtual const Medicament& cauta(const string& denumire) const = 0;
	virtual void sterge(const string& denumire) = 0;
	virtual ~Repository() = default;
};


/*
* Clasa responsabila cu stocarea medicamentelor intr-un vector
*/
class RepoMedicamente : public Repository
{
private:
	// vectorul care contine medicamentele
	//vector<Medicament> lista_med;
	vector<Medicament> lista_med;
public:

	// Constructorul de copiere- l-am sters pentru a impiedica copierea repository-ului
	RepoMedicamente(const RepoMedicamente& ot) = delete;

	// Constructorul default
	RepoMedicamente() = default;

	/*
	* Functie care adauga in lista un medicament
	* Date de intrare:- med- de tip Medicament
	* Date de iesire:-
	*				 ( daca Medicamentul este adaugat in lista)
	*				 - ridica exceptie de tipul RepoException daca medicamentul se afla deja in lista
	*/
	void adauga(const Medicament& med) override;

	/*
	* Functie care returneaza lista cu medicamente
	* Date de intrare:-
	* Date de iesire:- un vector cu medicamentele
	*/
	const vector<Medicament>& get_all()  override;

	/*
	* Functie care modifica datele unui medicament existent deja in lista
	* Date de intrare:- med_modif- de tip Medicament
	* Date de iesire:-
	*				 ( daca Medicamentul este modificat)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	void modifica(const Medicament& med_modif) override;

	/*
	* Functie care cauta un medicament in lista dupa denumire
	* Date de intrare:- denumire- de tip string
	* Date de iesire:- medicament- de tip Medicament (medicamentul cautat)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	const Medicament& cauta(const string& denumire) const override;

	/*
	* Functie care sterge un medicament din lista
	* Date de intrare:- denumire- de tip string
	* Date de iesire:-
	*				 (daca Medicamentul este sters)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	void sterge(const string& denumire) override;

	virtual ~RepoMedicamente() = default;

};

/*
* Clasa responsabila cu stocarea medicamentelor intr-un fisier. Mosteneste din RepoMedicamente
*/
class RepoMedicamenteFile :public RepoMedicamente {
private:
	string file_name;
	void loadFromFile();
	void storeToFile();
public:
	/*
	* Constructor. La apelarea acestuia se actualizeaza lista de medicamente cu continutul fisierului
	* Date de intrare:-file_name-string (numele fisierului unde vor fi stocate datele)
	*/
	RepoMedicamenteFile(string file_name) :RepoMedicamente(), file_name{ file_name }{
		loadFromFile();
	};

	// Constructorul de copiere- l-am sters pentru a impiedica copierea repository-ului
	RepoMedicamenteFile(const RepoMedicamenteFile& ot) = delete;

	/*
	* SUPRASCRIERE functie de adauga din RepoMedicamente
	* Functie care adauga in lista un medicament
	* Date de intrare:- med- de tip Medicament
	* Date de iesire:-
	*				 ( daca Medicamentul este adaugat in lista)
	*				 - ridica exceptie de tipul RepoException daca medicamentul se afla deja in lista
	*/
	void adauga(const Medicament& med) override;

	/*
	* SUPRASCRIERE functie de sterge din RepoMedicamente
	* Functie care sterge un medicament din lista
	* Date de intrare:- denumire- de tip string
	* Date de iesire:-
	*				 (daca Medicamentul este sters)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	void sterge(const string& denumire) override;

	/*
	* SUPRASCRIERE functie de modifica din RepoMedicamente
	* Functie care modifica datele unui medicament existent deja in lista
	* Date de intrare:- med_modif- de tip Medicament
	* Date de iesire:-
	*				 ( daca Medicamentul este modificat)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	void modifica(const Medicament& med) override;
};

class RepositoryMap :public Repository {
private:
	double probabilitate;
	map<string, Medicament> dict_med;
	vector<Medicament> get_medic;
public:
	RepositoryMap(double prob) :probabilitate{ prob } {}
	//RepositoryMap() = default;

	void adauga(const Medicament& med) override;
	const vector<Medicament>& get_all() override;
	void modifica(const Medicament& med_modif) override;
	const Medicament& cauta(const string& denumire) const override;
	void sterge(const string& denumire) override;

};

