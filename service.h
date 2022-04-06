#pragma once
#include "repository.h"
#include "validator.h"
#include "reteta.h"
#include "undo.h"
#include<string>
#include<vector>
#include<map>
#include <memory>

using std::map;
using std::string;
using std::vector;

/* Clasa DTO */
class MedicamenteProducator
{
private:
	/* contine numele producatorului si numarul de medicamente pentru fiecare producator */
	string producator;
	int nr_medic;
public:
	// Constructori
	MedicamenteProducator() { nr_medic = 0; }
	MedicamenteProducator(const string& producator, int nr_medic) :producator{ producator }, nr_medic{ nr_medic }{

	}
	/*
	* returneaza numarul de medicamente
	*/
	int get_nr_medic() const noexcept {
		return this->nr_medic;
	}
	/*
	* incrementeaza numarul de medicamente
	*/
	void creste_nr_medic() noexcept {
		this->nr_medic++;
	}
};

// tip de data ServiceMedicamente
class ServiceMedicamente
{
private:
	// service-ul contine o referinta la cate un obiect de tip RepoMedicamente, Validator si Reteta
	Repository& repo;
	Validator& valid;
	Reteta& reteta;
	vector<std::unique_ptr<ActiuneUndo>> undo;
public:

	/*
	* Constructorul service-ului
	* Date de intrare:-rep-de tip RepoMedicamente (responsabil cu stocarea medicamentelor)
	*				  -val- de tip Validator
	*				  -ret- de tip Reteta
	*/
	ServiceMedicamente(Repository& rep, Validator& val, Reteta& ret) noexcept :repo{ rep }, valid{ val }, reteta{ ret } {

	}

	// Constructorul de copiere- l-am sters pentru a impiedica copierea service-ului
	ServiceMedicamente(const ServiceMedicamente& ot) = delete;

	// Constructorul default
	ServiceMedicamente() = default;

	/*
	* Creeaza un medicament pe baza atributelor denumire,pret,producator,substanta, il valideaza si apoi il adauga in lista.
	* Date de intrare:-denumire-string
	*				  -pret-double
	*				  -producator-string
	*				  -substanta-string
	* Date de iesire:-
	*				 ( daca Medicamentul este adaugat in lista)
	*				 - ridica exceptie de tipul RepoException daca medicamentul se afla deja in lista
	*/
	void adauga_service(const string& denumire, double pret, const string& producator, const string& substanta);

	/*
	* Functie care returneaza lista cu medicamente
	* Date de intrare:-
	* Date de iesire:- un vector cu medicamentele
	*/
	const vector<Medicament>& get_all() const;

	/*
	* Creeaza un medicament pe baza atributelor denumire,pret,producator,substanta, il valideaza si apoi modifica datele
	* medicamentului cu aceeasi denumire existent deja in lista cu cele noi primite.
	* Date de intrare:-denumire-string
	*				  -pret-double
	*				  -producator-string
	*				  -substanta-string
	* Date de iesire:-
	*				 ( daca Medicamentul este modificat)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	void modifica_service(const string& denumire, double pret, const string& producator, const string& substanta);

	/*
	* Primeste o denumire, o valideaza si verifica daca medicamentul cu acea denumire se afla in lista.
	* In caz afirmativ returneaza medicamentul, altfel ridica exceptie
	* Date de intrare:- denumire- de tip string
	* Date de iesire:- medicament- de tip Medicament (medicamentul cautat)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	const Medicament& cauta_service(const string& denumire) const;

	/*
	* Primeste o denumire, o valideaza si verifica daca medicamentul cu acea denumire se afla in lista.
	* In caz afirmativ sterge medicamentul, altfel ridica exceptie.
	* Date de iesire:-
	*				 (daca Medicamentul este sters)
	*				 - ridica exceptie de tipul RepoException daca medicamentul nu se afla in lista
	*/
	void sterge_service(const string& denumire);


	/*
	* Functie care filtreaza lista de medicamente dupa pret
	* Date de intrare:-pret: double
	* Date de iesire:- returneaza o lista cu medicamentele care au pretul mai mare decat pret
	*/
	vector<Medicament> filtrare_pret(double pret);

	/*
	* Functie care filtreaza lista de medicamente dupa substanta
	* Date de intrare:-substanta: string
	* Date de iesire:- returneaza o lista cu medicamentele care contin substanta
	*/
	vector<Medicament> filtrare_substanta(const string& substanta);


	/*
	* Functie de sortare generala.
	* Date de intrare:-func- un pointer catre o functie care compara 2 medicamente
	*				       - verifica relatia de med1<med2 in functie de anumite criterii date ca parametru
	* Date de iesire:-returneaza o lista sortata dupa un anumit criteriu (VectorDinamic
	*/
	//vector<Medicament> sortare_generala(bool (*func)(const Medicament&, const Medicament&));

	/*
	* Functie care sorteaza lista de medicamente dupa denumire
	* Date de iesire:- returneaza lista sortata
	*/
	vector<Medicament> sortare_denumire();

	/*
	* Functie care sorteaza lista de medicamente dupa producator
	* Date de iesire:- returneaza lista sortata
	*/
	vector<Medicament> sortare_producator();

	/*
	* Functie care sorteaza lista de medicamente dupa substanta si pret
	* Date de iesire:- returneaza lista sortata
	*/
	vector<Medicament> sortare_substanta_pret();

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
	* Functie care adauga random un numar nr de medicamente existente in lista, pe reteta
	* Date de intrare:-nr-int
	*/
	void genereaza_reteta(int nr);

	/*
	* Functie care returneaza un dictionar cu numele producatorilor si numarul de medicamente pentru fiecare producator
	* Date de iesire:-un dictionar cu datele respective
	*/
	map<string, MedicamenteProducator> numarMedicamenteProducator();

	/*
	* Functie care exporta medicamentele din reteta intr-un fisier CSV.
	* Date de intrare:-nume_fis-string
	*/
	void exporta(const string& nume_fis) const;

	/*
	* Functie care efectueaza operatia de undo a ultimei operatii efectuate
	* Date de intrare:-
	* Date de iesire:- lista revine la starea anterioara ultimei operatii efectuate
	*				 - arunca exceptie de tip ValidException daca nu se poate efectua undo
	*/
	void Undo();

	Reteta& getRetetaCurenta()
	{
		return reteta;
	}

	// functii pt butoane dinamice care sterg medicamente
	vector<string> lista_producatori();
	void sterge_dupa_producator(const string& prod);

};

