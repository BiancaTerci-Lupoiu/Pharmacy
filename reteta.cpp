#include "reteta.h"
#include <random> // std::default_random_engine
#include <chrono>
#include <fstream>
void Reteta::goleste_reteta()
{
	reteta.clear();
	notify();
}

void Reteta::adauga_reteta(const string& denumire)
{
	const auto& gasit = repo.cauta(denumire);
	reteta.push_back(gasit);
	notify();
}

int Reteta::dimensiune_reteta() const noexcept
{
	return static_cast<unsigned int>(reteta.size());
}

const vector<Medicament>& Reteta::get_reteta() const noexcept
{
	return reteta;
}

void Reteta::genereaza_reteta(int nr)
{
	if (repo.get_all().size() < nr)
		throw RepoException("Nu avem atatea medicamente!\n");
	reteta.clear();
	reteta = repo.get_all();
	
	const auto seed = static_cast<size_t>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(reteta.begin(), reteta.end(), std::default_random_engine(static_cast<unsigned int>(seed)));
	//std::random_shuffle(reteta.begin(), reteta.end());
	reteta.erase(reteta.begin() + nr, reteta.end());
	notify();
}

void Reteta::exporta(const string& nume_fis) const
{

	string nume_fis_csv = nume_fis + ".csv";
	std::ofstream fout(nume_fis_csv);
	for (const auto& med : reteta)
		fout << med.get_denumire() << "," << med.get_pret() << "," << med.get_producator() << "," << med.get_substanta() << "\n";
	fout.close();
}
