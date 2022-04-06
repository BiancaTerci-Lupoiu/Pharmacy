#include "service.h"
#include <algorithm>


void ServiceMedicamente::adauga_service(const string& denumire, double pret, const string& producator, const string& substanta)
{
	Medicament med{ denumire,pret,producator,substanta };
	//validare
	this->valid.valideaza(med);
	this->repo.adauga(med);
	undo.push_back(std::make_unique<UndoAdauga>(repo, med));
}

const vector<Medicament>& ServiceMedicamente::get_all() const {
	return repo.get_all();
}

void ServiceMedicamente::modifica_service(const string& denumire, double pret, const string& producator, const string& substanta)
{
	Medicament med_modif{ denumire,pret,producator,substanta };
	//validare date
	this->valid.valideaza(med_modif);
	const auto& gasit = repo.cauta(med_modif.get_denumire());
	undo.push_back(std::make_unique<UndoModifica>(repo, gasit));
	repo.modifica(med_modif);
}

const Medicament& ServiceMedicamente::cauta_service(const string& denumire) const
{

	return repo.cauta(denumire);
}
void ServiceMedicamente::sterge_service(const string& denumire)
{
	const auto& gasit = repo.cauta(denumire);
	undo.push_back(std::make_unique<UndoSterge>(repo, gasit));
	repo.sterge(denumire);

}

vector<Medicament> ServiceMedicamente::filtrare_pret(double pret) {

	vector<Medicament> all;
	const auto& lista = repo.get_all();
	std::copy_if(lista.begin(), lista.end(), std::back_inserter(all), [pret](const Medicament& med) { return med.get_pret() > pret; });
	/*for (const auto& med : repo.get_all())
		if (med.get_pret()>=pret)
			all.push_back(med);*/
	return all;
}
vector<Medicament> ServiceMedicamente::filtrare_substanta(const string& substanta) {

	vector<Medicament> all;
	std::copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(all), [&substanta](const Medicament& med) {return med.get_substanta() == substanta; });
	/*for (const auto& med : repo.get_all())
		if (med.get_substanta() ==substanta)
			all.push_back(med);*/
	return all;
}

/*vector<Medicament> ServiceMedicamente::sortare_generala(bool (*func)(const Medicament&, const Medicament&))
{//func-returneaza true daca med1<=med2
	vector<Medicament> all{ repo.get_all() }; // fac o copie a listei de medicamente
	for(int i=0;i<all.size()-1;i++)
		for(int j=i+1;j<all.size();j++)
			if (!func(all[i], all[j]))
			{
				Medicament aux = all[i];
				all[i]=all[j];
				all[j] = aux;
			}
	return all;

}
*/
vector<Medicament> ServiceMedicamente::sortare_denumire()
{
	vector<Medicament> all{ repo.get_all() }; // fac o copie a listei de medicamente
	std::sort(all.begin(), all.end(), [](const Medicament& med1, const Medicament& med2) {
		return med1.get_denumire() < med2.get_denumire();
		});
	return all;
}
vector<Medicament> ServiceMedicamente::sortare_producator()
{
	vector<Medicament> all{ repo.get_all() }; // fac o copie a listei de medicamente
	std::sort(all.begin(), all.end(), [](const Medicament& med1, const Medicament& med2) {
		return med1.get_producator() < med2.get_producator();
		});
	return all;
}
vector<Medicament> ServiceMedicamente::sortare_substanta_pret()
{
	vector<Medicament> all{ repo.get_all() }; // fac o copie a listei de medicamente
	std::sort(all.begin(), all.end(), [](const Medicament& med1, const Medicament& med2) {
		if (med1.get_substanta() == med2.get_substanta())
			return med1.get_pret() < med2.get_pret();
		return med1.get_substanta() < med2.get_substanta();
		});
	return all;
}

void ServiceMedicamente::goleste_reteta()
{
	reteta.goleste_reteta();
}

void ServiceMedicamente::adauga_reteta(const string& denumire)
{
	reteta.adauga_reteta(denumire);
}

int ServiceMedicamente::dimensiune_reteta() const noexcept
{
	return reteta.dimensiune_reteta();
}

const vector<Medicament>& ServiceMedicamente::get_reteta() const noexcept
{
	return reteta.get_reteta();
}

void ServiceMedicamente::genereaza_reteta(int nr)
{
	reteta.genereaza_reteta(nr);
}

map<string, MedicamenteProducator> ServiceMedicamente::numarMedicamenteProducator()
{
	map<string, MedicamenteProducator> dict_prod_med;
	const auto& lista_medic = repo.get_all();
	for (const auto& medic : lista_medic)
	{
		if (dict_prod_med.find(medic.get_producator()) == dict_prod_med.end())
			dict_prod_med[medic.get_producator()] = MedicamenteProducator(medic.get_producator(), 1);
		else
			dict_prod_med[medic.get_producator()].creste_nr_medic();
	}
	return dict_prod_med;
}

void ServiceMedicamente::exporta(const string& nume_fis) const
{
	reteta.exporta(nume_fis);
}

void ServiceMedicamente::Undo()
{
	if (undo.empty())
		throw ValidException("Nu se poate face undo!\n");
	undo.back()->doUndo();
	undo.pop_back();

}

vector<string> ServiceMedicamente:: lista_producatori()
{
	vector<Medicament> meds = repo.get_all();
	vector<string> producatori;
	for (const auto& med : meds)
	{
		if (find_if(producatori.begin(), producatori.end(), [med](const string& p) { return p == med.get_producator();})==producatori.end())
		{
			producatori.push_back(med.get_producator());
		}
	}
	return producatori;
}

void ServiceMedicamente::sterge_dupa_producator(const string& prod)
{
	for (const auto& med : repo.get_all())
	{
		if (med.get_producator() == prod)
			sterge_service(med.get_denumire());
	}
}


