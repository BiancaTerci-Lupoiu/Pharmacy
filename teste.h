#pragma once
#include "medicament.h"
#include "repository.h"
#include "service.h"
#include "reteta.h"
//#include "vectordinamic.h"

void ruleaza_teste_sort_filtrare_reteta(RepoMedicamente& repo);

// ruleaza testele pe service
void ruleaza_teste_service(RepoMedicamente& repo);

// ruleaza testele pe repository
void ruleaza_teste_repo(Repository& repo);

// ruleaza testele pe domeniu- medicament
void ruleaza_teste_domeniu();

// ruleaza toate testele
void ruleaza_teste();

// ruleaza teste pe fisier
void ruleaza_teste_fisier();

// ruleaza teste functie de undo
void ruleaza_teste_undo();

void test_nou();
