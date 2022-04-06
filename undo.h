#pragma once
#include "medicament.h"
#include "repository.h"

// Clasa abstracta pentru implementare undo
class ActiuneUndo {
public:
	// functie virtuala, abstracta care va reface ultima operatie efectuata
	virtual void doUndo() = 0;

	// destructor
	virtual ~ActiuneUndo() = default;
};

// Clasa pentru implementare undo_adauga
class UndoAdauga :public ActiuneUndo {
private:
	Medicament med_adaugat;
	Repository& rep;
public:
	/*
	* Constructor
	* Date de intrare:-rep-Repository
	*				  -med_adaugat-Medicament (medicamentul care a fost adaugat in lista)
	*/
	UndoAdauga(Repository& rep, const Medicament& med) :rep{ rep }, med_adaugat{ med }{}

	/*
	* Functie care reface operatia de adauga (sterge ultimul medicament adaugat)
	* Date de iesire:- (se face undo la ultima operatie de adaugare)
	*/
	void doUndo() override {
		rep.sterge(med_adaugat.get_denumire());
	}
};

// Clasa pentru implementare undo_sterge
class UndoSterge :public ActiuneUndo {
private:
	Medicament med_sters;
	Repository& rep;
public:
	/*
	* Constructor
	* Date de intrare:-rep-Repository
	*				  -med_sters-Medicament (medicamentul care a fost sters din lista)
	*/
	UndoSterge(Repository& rep, const Medicament& med) :rep{ rep }, med_sters{ med }{}

	/*
	* Functie care reface operatia de sterge (adauga inapoi in lista ultimul medicament sters)
	* Date de iesire:- (se face undo la ultima operatie de sterge)
	*/
	void doUndo() override {
		rep.adauga(med_sters);
	}
};

// Clasa pentru implementare undo_modifica
class UndoModifica :public ActiuneUndo {
private:
	Medicament med_modif;
	Repository& rep;
public:

	/*
	* Constructor
	* Date de intrare:-rep-Repository
	*				  -med_modif-Medicament (medicamentul care a fost modificat in lista, inainte de modificare)
	*/
	UndoModifica(Repository& rep, const Medicament& med) :rep{ rep }, med_modif{ med }{}

	/*
	* Functie care reface operatia de modifica (modifica medicamentul la atributele anterioare modificarii)
	* Date de iesire:- (se face undo la ultima operatie de modifica)
	*/
	void doUndo() override {
		rep.modifica(med_modif);
	}
};


