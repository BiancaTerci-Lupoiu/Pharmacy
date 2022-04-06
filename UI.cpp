#include "UI.h"
#include<iostream>
#include<string>
#include<limits>
using std::cin;
using std::cout;
using std::string;

void UI::meniu()
{
	cout << "0-Exit\n1-Adauga\n2-Cauta\n3-Modifica\n4-Sterge\n5-Afisare\n6-Filtrare pret\n7-Filtrare substanta\n8-Sortare denumire\n9-Sortare producator\n10-Sortare substanta+pret\n";
	cout << "11-Reteta -adauga medicament\n12-Reteta -goleste reteta\n13-Reteta -genereaza reteta\n14-Reteta -afiseaza reteta\n15-Exporta reteta\n16-Raport\n17-Undo\n\n";
}

void UI::adauga_ui()
{
	string denumire, producator, substanta;
	double pret;
	cout << "Denumire: ";
	cin.ignore();
	std::getline(std::cin, denumire);
	cout << "Pret: ";
	cin >> pret;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Input gresit! Pretul trebuie sa fie un numar! " << "\n";
			cin >> pret;
		}
		if (!cin.fail())
			break;
	}
	cout << "Producator: ";
	cin.ignore();
	std::getline(std::cin, producator);
	cout << "Substanta activa: ";
	//cin.ignore();
	std::getline(std::cin, substanta);
	cout << "\n";
	srv.adauga_service(denumire, pret, producator, substanta);
}

void UI::modifica_ui()
{
	string denumire, producator, substanta;
	double pret;
	cout << "Denumire: ";
	cin.ignore();
	std::getline(std::cin, denumire);
	cout << "Pret: ";
	cin >> pret;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Input gresit! Pretul trebuie sa fie un numar! " << "\n";
			cin >> pret;
		}
		if (!cin.fail())
			break;
	}
	cout << "Producator: ";
	cin.ignore();
	std::getline(std::cin, producator);
	cout << "Substanta activa: ";
	//cin.ignore();
	std::getline(std::cin, substanta);
	cout << "\n";
	srv.modifica_service(denumire, pret, producator, substanta);
}
void UI::cauta_ui()
{
	string denumire;
	cout << "Denumire: ";
	cin >> denumire;
	const Medicament& med = srv.cauta_service(denumire);

	cout << "\nMedicamentul cautat:\n" << med.ToString() << "\n\n";


}
void UI::sterge_ui()
{
	string denumire;
	cout << "Denumire: ";
	cin >> denumire;
	cout << "\n";
	srv.sterge_service(denumire);
}

void UI::filtru_pret()
{
	double pret;
	cout << "Medicamente cu pretul mai mare decat: ";
	cin >> pret;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Input gresit! Pretul trebuie sa fie un numar! " << "\n";
			cin >> pret;
		}
		if (!cin.fail())
			break;
	}
	auto all = srv.filtrare_pret(pret);
	//const int
	size_t n = all.size();
	if (n == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const Medicament& med : all)
			cout << med.ToString() << "\n";
	}
	cout << "\n";

}

void UI::filtru_substanta()
{
	string substanta;
	cout << "Medicamente care contin substanta activa: ";
	cin >> substanta;

	auto all = srv.filtrare_substanta(substanta);
	size_t n = all.size();
	if (n == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const Medicament& med : all)
			cout << med.ToString() << "\n";
	}
	cout << "\n";

}

void UI::sortare1()
{
	vector<Medicament> all = srv.sortare_denumire();
	size_t n = all.size();
	if (n == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const Medicament& med : all)
			cout << med.ToString() << "\n";
	}
	cout << "\n";
}
void UI::sortare2()
{
	vector<Medicament> all = srv.sortare_producator();
	size_t n = all.size();
	if (n == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const Medicament& med : all)
			cout << med.ToString() << "\n";
	}
	cout << "\n";
}
void UI::sortare3()
{
	vector<Medicament> all = srv.sortare_substanta_pret();
	// am schimbat din const int?? dc nuj
	size_t n = all.size();
	if (n == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const Medicament& med : all)
			cout << med.ToString() << "\n";
	}
	cout << "\n";
}

void UI::adauga_reteta_ui()
{
	string denumire;
	cout << "Introdu denumirea medicamentului care urmeaza a fi adaugat in reteta: ";
	cin >> denumire;
	srv.adauga_reteta(denumire);
	const int n = srv.dimensiune_reteta();
	cout << "\nNumar medicamente pe reteta: " << n << "\n";

	cout << "\n";
}

void UI::goleste_reteta_ui()
{
	srv.goleste_reteta();
	const int n = srv.dimensiune_reteta();
	cout << "\nNumar medicamente pe reteta: " << n << "\n";

	cout << "\n";
}

void UI::genereaza_reteta()
{
	int nr;
	cout << "Introduceti numarul de medicamente care urmeaza a fi adaugate pe reteta: ";
	cin >> nr;
	size_t n = srv.get_all().size();
	if (nr > n || nr <= 0)
		cout << "Nu exista atatea medicamenete in lista!\n";
	else
	{
		srv.genereaza_reteta(nr);
		const int len = srv.dimensiune_reteta();
		cout << "\nNumar medicamente pe reteta: " << len << "\n";
	}
	cout << "\n";
}

void UI::afiseaza_reteta()
{
	const auto& reteta = srv.get_reteta();
	if (reteta.size() == 0)
		cout << "Nu exista medicamente in reteta!\n";
	else
		for (const auto& med : reteta)
			cout << med.ToString() << "\n";
	cout << "\n";
}

void UI::exporta_reteta()
{
	string nume_fis;
	cout << "Introdu numele fisierului: ";
	cin >> nume_fis;
	srv.exporta(nume_fis);
	cout << "Export realizat cu succes!\n";
}
void UI::raport()
{
	auto medic_produc = srv.numarMedicamenteProducator();
	if (medic_produc.size() == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const auto& item : medic_produc)
			cout << item.first << " " << item.second.get_nr_medic() << "\n";
	}
	cout << "\n";
}

void UI::undo_ui()
{
	srv.Undo();
	cout << "Undo realizat cu succes!\n\n";
}

void UI::afisare_medicamente()
{
	const auto& all = srv.get_all();
	size_t n = all.size();
	if (n == 0)
		cout << "Nu exista medicamente!\n";
	else
	{
		for (const Medicament& med : all)
			cout << med.ToString() << "\n";
	}
	cout << "\n";
}

void UI::start()
{
	while (true)
	{
		int cmd = -1;
		meniu();
		cout << "Introdu comanda: ";
		cin >> cmd;
		try {
			if (cmd == 0)
			{
				cout << "Adieu!\n";
				return;
			}
			else if (cmd == 1)
			{
				try {
					adauga_ui();
					cout << "Medicament adaugat cu succes!\n";
				}
				catch (const RepoException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
				catch (const ValidException& ex) {
					cout << ex.get_mesaj() << "\n";
				}

			}
			else if (cmd == 2)
			{
				try {
					cauta_ui();

				}
				catch (const RepoException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
			}
			else if (cmd == 3)
			{
				try {
					modifica_ui();
					cout << "Medicament modificat cu succes!\n";
				}
				catch (const RepoException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
				catch (const ValidException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
			}
			else if (cmd == 4)
			{
				try {
					sterge_ui();
					cout << "Medicament sters cu succes!\n";
				}
				catch (const RepoException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
			}
			else if (cmd == 5)
				afisare_medicamente();
			else if (cmd == 6)
				filtru_pret();
			else if (cmd == 7)
				filtru_substanta();
			else if (cmd == 8)
				sortare1();
			else if (cmd == 9)
				sortare2();
			else if (cmd == 10)
				sortare3();
			else if (cmd == 11)
			{
				try
				{
					adauga_reteta_ui();
				}
				catch (const RepoException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
			}
			else if (cmd == 12)
				goleste_reteta_ui();
			else if (cmd == 14)
				afiseaza_reteta();
			else if (cmd == 13)
				genereaza_reteta();
			else if (cmd == 15)
				exporta_reteta();
			else if (cmd == 16)
				raport();
			else if (cmd == 17)
			{
				try
				{
					undo_ui();
				}
				catch (const ValidException& ex) {
					cout << ex.get_mesaj() << "\n";
				}
			}
			else
				cout << "Comanda invalida!\n";
		}
		catch (const RepoException& ex) {
			cout << ex.get_mesaj() << "\n";
		}
	}
}
