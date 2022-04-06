#include "repository.h"
#include<fstream>
#include <random>
string RepoException::get_mesaj() const {
	return msg;
}

// RepoMemory
void RepoMedicamente::adauga(const Medicament& med)
{
	for (const Medicament& medic : lista_med)
	{
		if (med == medic)
			throw RepoException("Medicament existent!\n");

	}

	lista_med.push_back(med);
}

const vector<Medicament>& RepoMedicamente::get_all() {
	return lista_med;
}

void RepoMedicamente::modifica(const Medicament& med_modif) {
	for (Medicament& medic : lista_med)
	{
		if (med_modif == medic)
		{
			medic = med_modif;
			return;
		}
	}
	throw RepoException("Medicament inexistent!\n");
}

const Medicament& RepoMedicamente::cauta(const string& denumire) const
{
	auto rez = find_if(lista_med.begin(), lista_med.end(), [&denumire](const Medicament& medic) {return medic.get_denumire() == denumire; });
	if (rez == lista_med.end())
		throw RepoException("Medicament inexistent!\n");
	return *rez;

}

void RepoMedicamente::sterge(const string& denumire)
{
	size_t n = lista_med.size();
	int i;
	for (i = 0; i < n; i++)
	{
		if (lista_med.at(i).get_denumire() == denumire)
		{
			lista_med.erase(lista_med.begin() + i);
			return;
		}
	}
	throw RepoException("Medicament inexistent!\n");
}

// RepoFile
void RepoMedicamenteFile::adauga(const Medicament& med)
{
	RepoMedicamente::adauga(med);
	storeToFile();
}

void RepoMedicamenteFile::sterge(const string& denumire)
{
	RepoMedicamente::sterge(denumire);
	storeToFile();
}

void RepoMedicamenteFile::modifica(const Medicament& med)
{
	RepoMedicamente::modifica(med);
	storeToFile();
}

void RepoMedicamenteFile::loadFromFile()
{
	std::ifstream fin(file_name);
	if (!fin.is_open())
		throw RepoException("Eroare la deschiderea fisierului\n");

	while (!fin.eof())
	{
		string denumire, producator, substanta;
		double pret = 0;
		fin >> denumire;
		if (fin.eof())
			break;
		fin >> pret >> producator >> substanta;
		Medicament med{ denumire,pret,producator,substanta };
		RepoMedicamente::adauga(med);

	}
	fin.close();
}

void RepoMedicamenteFile::storeToFile()
{
	std::ofstream fout(file_name);
	/*if (!fout.is_open())
		throw RepoException("Eroare la deschiderea fisierului\n");*/
	for (const auto& med : RepoMedicamente::get_all())
	{
		fout << med.get_denumire() << " " << med.get_pret() << " " << med.get_producator() << " " << med.get_substanta() << "\n";
	}
	fout.close();
}

// RepoMap
void RepositoryMap::adauga(const Medicament& med)
{
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	std::cout << "Probabilitatea este: " << nr << "\n";
	if (probabilitate > nr)
		throw RepoException("Probabilitate mica!\n");
	else
	{
		for (const auto& medic : dict_med)
		{
			if (med.get_denumire() == medic.second.get_denumire())
				throw RepoException("Medicament existent!\n");
		}
		dict_med[med.get_denumire()] = med;
	}
}

void RepositoryMap::modifica(const Medicament& med_modif)
{
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	std::cout << "Probabilitatea este: " << nr << "\n";
	if (probabilitate > nr)
		throw RepoException("Probabilitate mica!\n");
	else
	{
		for (auto& medic : dict_med)
		{
			if (med_modif == medic.second)
			{
				medic.second = med_modif;
				return;
			}
		}
		throw RepoException("Medicament inexistent!\n");
	}
}

const Medicament& RepositoryMap::cauta(const string& denumire) const
{
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	std::cout << "Probabilitatea este: " << nr << "\n";
	if (probabilitate > nr)
		throw RepoException("Probabilitate mica!\n");

	for (const auto& medic : dict_med)
	{
		if (medic.second.get_denumire() == denumire)
			return medic.second;
	}
	throw RepoException("Medicament inexistent!\n");

}

void RepositoryMap::sterge(const string& denumire)
{
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	std::cout << "Probabilitatea este: " << nr << "\n";
	if (probabilitate > nr)
		throw RepoException("Probabilitate mica!\n");
	else
	{
		for (const auto& medic : dict_med)
		{
			if (medic.second.get_denumire() == denumire)
			{
				dict_med.erase(denumire);
				return;
			}
		}
		throw RepoException("Medicament inexistent!\n");
	}
}

const vector<Medicament>& RepositoryMap::get_all()
{
	/*double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	std::cout << "Probabilitatea este: " << nr << "\n";
	if (probabilitate <= nr)
		throw RepoException("Probabilitate mica!\n");
		*/
	get_medic.clear();
	for (const auto& medic : dict_med)
		get_medic.push_back(medic.second);
	return get_medic;
}




