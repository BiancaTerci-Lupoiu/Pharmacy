#include "teste.h"
#include<assert.h>
#include<math.h>
#include<iostream>
#include<fstream>
#define file_name "repo_test.txt"

void ruleaza_teste_domeniu()
{
	Medicament med1{ "paracetamol",100.5,"S.C.Hunedoara","ranitidinum" };
	assert(med1.get_denumire() == "paracetamol");
	assert(fabs(med1.get_pret() - 100.5) < 0.00001);
	assert(med1.get_producator() == "S.C.Hunedoara");
	assert(med1.get_substanta() == "ranitidinum");
	Medicament med2{ "paracetamol",200,"S.C.Eu","ranitidinum" };
	assert(med1 == med2);
	assert(med2.ToString() == "Denumire: paracetamol | pret: 200.000000 | producator: S.C.Eu | substanta activa: ranitidinum");
	med2 = med1;
	assert(med1.get_producator() == med2.get_producator());

}
void ruleaza_teste_repo(Repository& repo)
{
	//RepoMedicamente repo;
	Medicament med{ "paracetamol",100.5,"S.C.Hunedoara","ranitidinum" };
	Medicament med1{ "aspirina",50.9,"S.C.BaiaMare","ranitidinum" };
	Medicament med2{ "paracetamol",200,"S.C.Eu","ranitidinum" };

	//adauga + get_all
	repo.adauga(med);
	repo.adauga(med1);
	const auto& all = repo.get_all();
	assert(all.size() == 2);
	try {
		repo.adauga(med2);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament existent!\n");
		assert(true);
	}

	//cauta
	const auto& gasit = repo.cauta("paracetamol");
	assert(gasit == med);
	assert(fabs(gasit.get_pret() - med.get_pret()) < 0.0001);
	try {
		repo.cauta("bla");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}

	//modifica
	Medicament med_modif{ "aspirina",90,"undeva","ceva" };
	repo.modifica(med_modif);
	const Medicament& gasit1 = repo.cauta("aspirina");
	assert(gasit1 == med_modif);
	assert(gasit1.get_pret() == med_modif.get_pret());
	assert(gasit1.get_producator() == med_modif.get_producator());
	assert(gasit1.get_substanta() == med_modif.get_substanta());
	Medicament med_rau{ "nebun",10,"bla","blabla" };
	try {
		repo.modifica(med_rau);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}

	//sterge
	repo.sterge("aspirina");
	const auto& all2 = repo.get_all();
	assert(all2.size() == 1);
	try {
		repo.sterge("aspirina");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}



}
void ruleaza_teste_service(RepoMedicamente& repo)
{
	//RepoMedicamente repo;
	Validator valid;
	Reteta reteta{ repo };
	ServiceMedicamente srv{ repo,valid,reteta };
	Medicament med{ "paracetamol",100.5,"S.C.Hunedoara","ranitidinum" };
	Medicament med1{ "aspirina",50.9,"S.C.BaiaMare","ranitidinum" };
	Medicament med2{ "paracetamol",200,"S.C.Eu","ranitidinum" };

	//adauga
	srv.adauga_service("paracetamol", 100.5, "S.C.Hunedoara", "ranitidinum");
	srv.adauga_service("aspirina", 50.9, "S.C.BaiaMare", "ranitidinum");
	const auto& all = srv.get_all();
	assert(all.size() == 2);
	try {
		srv.adauga_service("paracetamol", 200, "S.C.Eu", "ranitidinum");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament existent!\n");
		assert(true);
	}
	try {
		srv.adauga_service("", -200, "", "");
		assert(false);
	}
	catch (const ValidException& e) {
		assert(e.get_mesaj() == "Denumire invalida!\nPret invalid!\nProducator invalid!\nSubstanta invalida!\n");
		assert(true);
	}

	//modifica + cauta
	srv.modifica_service("paracetamol", 500.85, "altundeva", "cocos");
	const auto& gasit = srv.cauta_service("paracetamol");
	const auto& all1 = srv.get_all();
	assert(all1.size() == 2);
	assert(fabs(500.85 - gasit.get_pret()) < 0.001);
	assert("altundeva" == gasit.get_producator());
	assert("cocos" == gasit.get_substanta());
	try {
		srv.modifica_service("nue", 200, "S.C.Eu", "ranitidinum");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}
	try {
		srv.modifica_service("", -200, "", "");
		assert(false);
	}
	catch (const ValidException& e) {
		assert(e.get_mesaj() == "Denumire invalida!\nPret invalid!\nProducator invalid!\nSubstanta invalida!\n");
		assert(true);
	}

	//cauta
	try {
		srv.cauta_service("nue");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}

	//sterge
	srv.sterge_service("paracetamol");
	const auto& all2 = srv.get_all();
	assert(all2.size() == 1);
	try {
		srv.sterge_service("nue");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}


}

void ruleaza_teste_sort_filtrare_reteta(RepoMedicamente& repo)
{
	//RepoMedicamente repo;
	Validator valid;
	Reteta reteta{ repo };
	assert(reteta.get_all().size() == 0);
	ServiceMedicamente srv{ repo,valid,reteta };
	//filtrari
	srv.adauga_service("aspirina", 50.9, "S.C.BaiaMare", "ranitidinum");
	srv.adauga_service("paracetamol", 1000.5, "S.C.Hunedoara", "ranitidinum");
	srv.adauga_service("nurofen", 50.9, "S.C.BaiaMare", "absolut");
	srv.adauga_service("fervex", 100.5, "S.C.Hunedoara", "ranitidinum");
	srv.adauga_service("algocalmin", 234, "Aoleu", "absolut");

	assert(srv.filtrare_pret(101).size() == 2);
	assert(srv.filtrare_pret(100).size() == 3);
	assert(srv.filtrare_substanta("absolut").size() == 2);
	assert(srv.filtrare_substanta("ex").size() == 0);

	//sortari
	auto alls = srv.sortare_denumire();
	assert(alls.size() == 5);
	assert(alls[0].get_denumire() == "algocalmin");
	assert(alls[4].get_denumire() == "paracetamol");
	auto alls1 = srv.sortare_producator();
	assert(alls1[0].get_producator() == "Aoleu");
	assert(alls1[4].get_producator() == "S.C.Hunedoara");
	auto alls2 = srv.sortare_substanta_pret();
	assert(alls2[0].get_denumire() == "nurofen");
	assert(alls2[1].get_denumire() == "algocalmin");
	assert(alls2[4].get_denumire() == "paracetamol");

	//test ensure_capacity
	srv.adauga_service("ala", 234, "Aoleu", "absolut");
	assert(srv.get_all().size() == 6);

	//reteta
	srv.adauga_reteta("algocalmin");
	srv.adauga_reteta("nurofen");
	assert(srv.dimensiune_reteta() == 2);
	try
	{
		srv.adauga_reteta("n-avem");
		assert(false);
	}
	catch (const RepoException& e)
	{
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}
	const auto& reteta_medic = srv.get_reteta();
	assert(reteta_medic[0].get_denumire() == "algocalmin");
	assert(reteta_medic[1].get_denumire() == "nurofen");
	srv.goleste_reteta();
	assert(srv.dimensiune_reteta() == 0);

	// ca sa treaca testele de la functia asta
	assert(srv.getRetetaCurenta().dimensiune_reteta()==0);

	srv.genereaza_reteta(4);
	assert(srv.dimensiune_reteta() == 4);
	try
	{
		srv.genereaza_reteta(20);
		assert(false);
	}
	catch (const RepoException& e)
	{
		assert(e.get_mesaj() == "Nu avem atatea medicamente!\n");
		assert(true);
	}

	// reteta-export
	srv.exporta("test_export");
	std::ifstream fin("test_export.csv");
	int nr = 0;
	string buff;
	while (fin >> buff)
		nr++;
	assert(nr == 4);
	
	
	// teste raport

	auto dict_med_produc = srv.numarMedicamenteProducator();
	assert(dict_med_produc["S.C.BaiaMare"].get_nr_medic() == 2);
	assert(dict_med_produc["S.C.Hunedoara"].get_nr_medic() == 2);
	assert(dict_med_produc["Aoleu"].get_nr_medic() == 2);

	
}

void ruleaza_teste_fisier()
{
	Medicament med = Medicament("aa", 25, "bb", "cc");
	try {
		RepoMedicamenteFile repo{ "nu" };
	}
	catch (const RepoException& ex)
	{
		assert(ex.get_mesaj() == "Eroare la deschiderea fisierului\n");
	}

}
void ruleaza_teste_undo()
{
	RepoMedicamente repo;
	Validator valid;
	Reteta reteta{ repo };
	ServiceMedicamente srv{ repo,valid,reteta };
	try
	{
		srv.Undo();
	}
	catch (const ValidException& ex)
	{
		assert(ex.get_mesaj() == "Nu se poate face undo!\n");
	}
	srv.adauga_service("aspirina", 50.9, "S.C.BaiaMare", "ranitidinum");
	srv.adauga_service("paracetamol", 1000.5, "S.C.Hunedoara", "ranitidinum");
	assert(srv.get_all().size() == 2);
	srv.modifica_service("aspirina", 20, "aaa", "bbb");
	assert(srv.cauta_service("aspirina").get_producator() == "aaa");
	srv.Undo();
	assert(srv.cauta_service("aspirina").get_producator() == "S.C.BaiaMare");
	srv.sterge_service("aspirina");
	assert(srv.get_all().size() == 1);
	srv.Undo();
	assert(srv.get_all().size() == 2);
	srv.Undo();
	assert(srv.get_all().size() == 1);

}

/*void test_nou()
{
	const double prob = 0;
	RepositoryMap repo{ prob };
	Medicament med{ "paracetamol",100.5,"S.C.Hunedoara","ranitidinum" };
	Medicament med1{ "aspirina",50.9,"S.C.BaiaMare","ranitidinum" };
	Medicament med2{ "paracetamol",200,"S.C.Eu","ranitidinum" };

	//adauga + get_all
	repo.adauga(med);
	repo.adauga(med1);
	const auto& all = repo.get_all();
	assert(all.size() == 2);
	try {
		repo.adauga(med2);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament existent!\n");
		assert(true);
	}

	//cauta
	const auto& gasit = repo.cauta("paracetamol");
	assert(gasit == med);
	assert(fabs(gasit.get_pret() - med.get_pret()) < 0.0001);
	try {
		repo.cauta("bla");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}

	//modifica
	Medicament med_modif{ "aspirina",90,"undeva","ceva" };
	repo.modifica(med_modif);
	const Medicament& gasit1 = repo.cauta("aspirina");
	assert(gasit1 == med_modif);
	assert(gasit1.get_pret() == med_modif.get_pret());
	assert(gasit1.get_producator() == med_modif.get_producator());
	assert(gasit1.get_substanta() == med_modif.get_substanta());
	Medicament med_rau{ "nebun",10,"bla","blabla" };
	try {
		repo.modifica(med_rau);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}

	//sterge
	repo.sterge("aspirina");
	const auto& all2 = repo.get_all();
	assert(all2.size() == 1);
	try {
		repo.sterge("aspirina");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_mesaj() == "Medicament inexistent!\n");
		assert(true);
	}



}*/

void ruleaza_teste()
{// golesc fisierul inainte sa creez repoFile-ul!!
	std::ofstream fout1(file_name);
	fout1 << "";
	fout1.close();
	ruleaza_teste_domeniu();

	RepoMedicamente repo1;
	RepoMedicamenteFile repof1{ file_name };

	ruleaza_teste_repo(repo1);
	ruleaza_teste_repo(repof1);

	std::ofstream fout2(file_name);
	fout2 << "";
	fout2.close();
	RepoMedicamente repo2;
	RepoMedicamenteFile repof2{ file_name };

	ruleaza_teste_service(repo2);
	ruleaza_teste_service(repof2);

	std::ofstream fout3(file_name);
	fout3 << "";
	fout3.close();
	RepoMedicamente repo3;
	RepoMedicamenteFile repof3{ file_name };
	ruleaza_teste_sort_filtrare_reteta(repo3);
	ruleaza_teste_sort_filtrare_reteta(repof3);

	ruleaza_teste_fisier();
	ruleaza_teste_undo();
	//test_nou();
	constexpr double prob = 0;
	RepositoryMap repo{ prob };
	ruleaza_teste_repo(repo);
}




