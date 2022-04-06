#include "Lab10QT.h"
#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 
#include "teste.h"
#include "UI.h"
#include "gui.h"

int main(int argc, char *argv[])
{
	ruleaza_teste();

	{
		QApplication a(argc, argv);
		//constexpr double probabilitate = 0.7;
		RepoMedicamenteFile repo{ "repo.txt" };
		//RepoMedicamente repo;
		//RepositoryMap repo{ probabilitate };
		Validator valid;
		Reteta reteta{ repo };
		ServiceMedicamente srv{ repo,valid,reteta };
		MyGUI gui{ srv };
		gui.show();
		return a.exec();
	}

}


