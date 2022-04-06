#include "gui.h"
#include<QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <qmessagebox.h>
#include <QString>
#include <qdebug.h>
void MyGUI::initGUIComp()
{
	QPalette p(palette());
	p.setColor(QPalette::Window, QColor::QColor("#8b008b"));
	p.setColor(QPalette::Base, QColor::QColor("#dda0dd"));
	p.setColor(QPalette::WindowText, QColor::QColor("#ffff00"));
	setPalette(p);

	QVBoxLayout* layout_principal = new QVBoxLayout;
	setLayout(layout_principal);

	QHBoxLayout* main_ly = new QHBoxLayout;
	layout_principal->addLayout(main_ly);
	// layout pt lista+butoane pe lista
	QVBoxLayout* ly = new QVBoxLayout;
	ly->addWidget(listaMed);
	// layout butoane sortare
	QHBoxLayout* butoane_lista_ly = new QHBoxLayout;
	butoane_lista_ly->addWidget(btnSortDenumire);
	butoane_lista_ly->addWidget(btnSortProducator);
	butoane_lista_ly->addWidget(btnSortSubstantaP);
	ly->addLayout(butoane_lista_ly);
	// layout butoane refresh exit
	QHBoxLayout* butoane_utils = new QHBoxLayout;
	butoane_utils->addWidget(btnRefresh);
	butoane_utils->addWidget(btnExit);
	butoane_utils->addWidget(btnUndo);
	ly->addLayout(butoane_utils);
	main_ly->addLayout(ly);
	// vertical layout pentru form+operatii crud
	QVBoxLayout* ly2 = new QVBoxLayout;
	// form layout addRow(label,QLineEdit)
	QFormLayout* form_ly = new QFormLayout;
	form_ly->addRow("Denumire", editDenumire);
	form_ly->addRow("Pret", spinPret);
	spinPret->setMaximum(10000);
	//form_ly->addRow("Pret", editPret);
	form_ly->addRow("Producator", editProducator);
	form_ly->addRow("Substanta", editSubstanta);
	ly2->addLayout(form_ly);
	// horizontal layout pentru butoanele pentru operatii crud(adauga,modifica,sterge)
	// nu arata bine-de modificat
	QHBoxLayout* crud1_ly = new QHBoxLayout;
	crud1_ly->addWidget(btnAdauga);
	crud1_ly->addWidget(btnModifica);
	crud1_ly->addWidget(btnSterge);
	crud1_ly->setAlignment(Qt::AlignTop);
	ly2->addLayout(crud1_ly);

	// form layout pt cauta si filtrari
	QFormLayout* form_ly2 = new QFormLayout;
	form_ly2->addRow(btnCauta, editCauta);
	//form_ly2->addRow(btnFiltruPret, editFiltruPret);
	form_ly2->addRow(btnFiltruPret, sliderFiltrarePret);
	sliderFiltrarePret->setRange(0, 6000);
	form_ly2->addRow("Pret filtrare: ", labelslider);
	form_ly2->addRow(btnFiltruSubstanta, editFiltruSubstanta);
	ly2->addLayout(form_ly2);
	main_ly->addLayout(ly2);
	//QTableWidgetItem* titem = new QTableWidgetItem{ QString::fromStdString("denumire") };
	//tabel->setHorizontalHeaderItem(0, titem);
	main_ly->addWidget(tabel);

	// tot ce tine de reteta
	QVBoxLayout* buton_reteta_ly = new QVBoxLayout;
	// setez culoarea pt label
	infoReteta->setStyleSheet("background-color: yellow;font: 12pt;");
	buton_reteta_ly->addWidget(infoReteta);
	buton_reteta_ly->addWidget(btnGoleste);
	QFormLayout* form_reteta = new QFormLayout;
	form_reteta->addRow(btnAdaugaReteta, comboAdauga);
	form_reteta->addRow(btnGenereaza, spinGenereaza);
	//form_reteta->addRow(btnGenereaza, editGenereaza);
	form_reteta->addRow(btnExport, editExport);
	buton_reteta_ly->addLayout(form_reteta);
	buton_reteta_ly->addWidget(btnReteta);
	buton_reteta_ly->addWidget(btnRetetaRead);
	buton_reteta_ly->addWidget(btnRaport);
	main_ly->addLayout(buton_reteta_ly);

	// fereastra raport
	raport->setWindowTitle("Raport");
	int x = raport->width() * 0.5;
	int y = raport->height() * 0.8;
	raport->setFixedSize(x, y);
	QVBoxLayout* raport_ly = new QVBoxLayout;
	raport->setLayout(raport_ly);
	raport_ly->addWidget(tabel_raport);
	tabel_raport->setHorizontalHeaderItem(0, new QTableWidgetItem("Producator"));
	tabel_raport->setHorizontalHeaderItem(1, new QTableWidgetItem("Nr. Medicamente"));

	main_ly->addLayout(lybtndin);

	// pt tablemodel
	layout_principal->addWidget(tableview);
	tableview->setModel(model);
	
}
void MyGUI::initSignals()
{
	QObject::connect(btnSortDenumire, &QPushButton::clicked, this, [=]() {
		populateList(srv.sortare_denumire());
		});
	QObject::connect(btnSortProducator, &QPushButton::clicked, this, [=]() {
		populateList(srv.sortare_producator());
		});
	QObject::connect(btnSortSubstantaP, &QPushButton::clicked, this, [=]() {
		populateList(srv.sortare_substanta_pret());
		});
	QObject::connect(btnRefresh, &QPushButton::clicked, this, [=]() {
		populateList(srv.get_all());
		editCauta->setText("");
		//editFiltruPret->setText("");
		sliderFiltrarePret->setValue(0);
		editFiltruSubstanta->setText("");
		
		});
	QObject::connect(btnExit, &QPushButton::clicked, this, [=]() {
		QMessageBox::information(this,"Exit","Adieu!");
		// close inchide fereastra QWidget
		close();
		});
	// conectez item-urile din lista ca sa afiseze detalii despre medicamente in form
	QObject::connect(listaMed, &QListWidget::itemSelectionChanged, [=]() {
		// returneaza o lista (selectedItems) cu cele selectate
		auto selItems = listaMed->selectedItems();
		if (selItems.isEmpty())
		{
			editDenumire->setText("");
			//editPret->setText("");
			spinPret->setValue(0);
			editSubstanta->setText("");
			editProducator->setText("");
		}
		else
		{
			// iau prima selectata
			auto selItem = selItems.at(0);
			QString denumire = (selItem->data(Qt::UserRole)).toString();
			const auto& med = srv.cauta_service(denumire.toStdString());
			editDenumire->setText(selItem->text());
			//editPret->setText(QString::number(med.get_pret()));
			spinPret->setValue(med.get_pret());
			editSubstanta->setText(QString::fromStdString(med.get_substanta()));
			editProducator->setText(QString::fromStdString(med.get_producator()));
		}

		});
	QObject::connect(btnAdauga, &QPushButton::clicked, this, &MyGUI::adauga_gui);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &MyGUI::modifica_gui);
	QObject::connect(tabel, &QTableWidget::itemSelectionChanged, [=]() {
		// returneaza o lista (selectedItems) cu cele selectate
		auto selItems = tabel->selectedItems();
		if (selItems.isEmpty())
		{
			editDenumire->setText("");
			//editPret->setText("");
			spinPret->setValue(0);
			editSubstanta->setText("");
			editProducator->setText("");
		}
		else
		{
			// iau prima selectata
			auto selItem = selItems.at(0);
			auto denumire = selItem->text().toStdString();
			const auto& med = srv.cauta_service(denumire);
			editDenumire->setText(selItem->text());
			//editPret->setText(QString::number(med.get_pret()));
			spinPret->setValue(med.get_pret());
			editSubstanta->setText(QString::fromStdString(med.get_substanta()));
			editProducator->setText(QString::fromStdString(med.get_producator()));
		}

		});
	QObject::connect(btnSterge, &QPushButton::clicked, this, &MyGUI::sterge_gui);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &MyGUI::undo_gui);
	QObject::connect(btnCauta, &QPushButton::clicked, this, &MyGUI::cauta_gui);
	QObject::connect(btnFiltruPret, &QPushButton::clicked, this, &MyGUI::filtru_pret_gui_colorare);
	QObject::connect(btnFiltruSubstanta, &QPushButton::clicked, this, &MyGUI::filtru_substanta_gui_colorare);
	/*QObject::connect(btnReteta, &QPushButton::clicked, this, [&]() {
		reteta->show();
		});*/
	QObject::connect(btnRaport, &QPushButton::clicked, this, &MyGUI::raport_gui);
	QObject::connect(btnReteta, &QPushButton::clicked, this, &MyGUI::show_reteta_crud);
	QObject::connect(btnRetetaRead, &QPushButton::clicked, this, &MyGUI::show_reteta_read);

	// conectez butoanele pt reteta din main window
	QObject::connect(btnGoleste, &QPushButton::clicked, this, &MyGUI::goleste_reteta_gui);
	QObject::connect(btnAdaugaReteta, &QPushButton::clicked, this, &MyGUI::add_reteta_gui);
	QObject::connect(btnGenereaza, &QPushButton::clicked, this, &MyGUI::genereaza_reteta_gui);
	QObject::connect(btnExport, &QPushButton::clicked, this, &MyGUI::export_reteta_gui);

	QObject::connect(sliderFiltrarePret, &QSlider::valueChanged, this, [=]() {
		labelslider->setText(QString::number(sliderFiltrarePret->value()));
		});

	// conectam table view
	QObject::connect(tableview->selectionModel(), &QItemSelectionModel::selectionChanged, [=]() {

		auto selitems = tableview->selectionModel()->selectedIndexes();
		if (selitems.isEmpty())
		{
			editDenumire->setText("");
			//editPret->setText("");
			spinPret->setValue(0);
			editSubstanta->setText("");
			editProducator->setText("");
		}
		else
		{
			// selrow va contine linia elementului selectat
			auto selrow = selitems.at(0).row();
			// creez QModelIndexes pt fiecare celula din linia respectiva
			auto cel0 = tableview->model()->index(selrow, 0);
			auto cel1 = tableview->model()->index(selrow, 1);
			auto cel2 = tableview->model()->index(selrow, 2);
			auto cel3 = tableview->model()->index(selrow, 3);
			// pentru data am nevoie de un QModelIndex
			// iau datele din tabel
			auto denumire = tableview->model()->data(cel0, Qt::UserRole).toString();
			auto pret = tableview->model()->data(cel1, Qt::DisplayRole).toDouble();
			auto producator = tableview->model()->data(cel2, Qt::DisplayRole).toString();
			auto substanta = tableview->model()->data(cel3, Qt::DisplayRole).toString();

			// setez qlineedit urile cu datele
			editDenumire->setText(denumire);
			spinPret->setValue(pret);
			editProducator->setText(producator);
			editSubstanta->setText(substanta);
		}

		});

}
void MyGUI::initialState()
{
	populateList(srv.get_all());
	
}

void MyGUI::populateList(const vector<Medicament>&lista_med)
{
	listaMed->clear();
	tabel->clear();
	tabel->setRowCount(0);
	for (const Medicament& med : lista_med)
	{
		auto text = med.get_denumire();
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(text) };
		item->setData(Qt::UserRole, QString::fromStdString(text));
		listaMed->addItem(item);
		// pentru tabel:
		QTableWidgetItem* titem = new QTableWidgetItem{ QString::fromStdString(text) };
		
		tabel->insertRow(tabel->rowCount());
		tabel->setItem(tabel->rowCount() - 1,0,titem);
		
	}

	populateComboBox();
	adauga_butoane_dinamic();
	reloadList(lista_med);
	model->colorare_filtru(vector<Medicament>());
}
void MyGUI::populateComboBox()
{
	comboAdauga->clear();
	auto lista_med = srv.get_all();
	for (const auto& med : lista_med)
	{
		auto denumire = med.get_denumire();
		comboAdauga->addItem(QString::fromStdString(denumire));
	}
}

void MyGUI::show_reteta_crud()
{
	auto Retetacrud = new RetetaGUI(srv.getRetetaCurenta());
	Retetacrud->show();
}
void MyGUI::show_reteta_read()
{
	auto Retetareadonly = new RetetaReadOnlyGUI(srv.getRetetaCurenta());
	Retetareadonly->show();
}

void MyGUI::adauga_butoane_dinamic()
{
	
	while(auto x=lybtndin->takeAt(0))
	{
		delete x->widget();
		delete x;
	}
	
	vector<string> producatori = srv.lista_producatori();
	for (const auto& prod : producatori)
	{
		QPushButton* btn = new QPushButton(QString::fromStdString(prod));
		lybtndin->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, this, [=]() {
			srv.sterge_dupa_producator(prod);
			populateList(srv.get_all());
			
			});
	}
}


void MyGUI::adauga_gui()
{
	string denumire = editDenumire->text().toStdString();
	//double pret = editPret->text().toDouble();
	double pret = spinPret->value();
	string producator = editProducator->text().toStdString();
	string substanta = editSubstanta->text().toStdString();
	try
	{
		srv.adauga_service(denumire, pret, producator, substanta);
		populateList(srv.get_all());
	}
	catch(const RepoException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
	catch (const ValidException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
}
void MyGUI::modifica_gui()
{
	auto denumire = editDenumire->text().toStdString();
	//auto pret = editPret->text().toDouble();
	double pret = spinPret->value();
	auto producator = editProducator->text().toStdString();
	auto substanta = editSubstanta->text().toStdString();
	try
	{
		srv.modifica_service(denumire, pret, producator, substanta);
		populateList(srv.get_all());
	}
	catch (const RepoException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
	catch (const ValidException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
}

void MyGUI::sterge_gui()
{
	auto denumire = editDenumire->text().toStdString();
	try
	{
		srv.sterge_service(denumire);
		populateList(srv.get_all());
	}
	catch (const RepoException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
}

void MyGUI::undo_gui()
{
	try
	{
		srv.Undo();
		populateList(srv.get_all());
	}
	catch (const ValidException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
}

void MyGUI::cauta_gui()
{
	auto denumire = editCauta->text().toStdString();
	if(denumire=="")
		QMessageBox::warning(this, "Eroare", "Camp cautare vid!");
	else
	{
		try
		{
			auto gasit = srv.cauta_service(denumire);
			editDenumire->setText(QString::fromStdString(gasit.get_denumire()));
			//editPret->setText(QString::number(gasit.get_pret()));
			spinPret->setValue(gasit.get_pret());
			editProducator->setText(QString::fromStdString(gasit.get_producator()));
			editSubstanta->setText(QString::fromStdString(gasit.get_substanta()));
		}
		catch (const RepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
		}
	}
}

void MyGUI::filtru_pret_gui()
{
	//bool ok;
	//auto pret = editFiltruPret->text().toDouble(&ok);
	double pret = sliderFiltrarePret->value();
	populateList(srv.filtrare_pret(pret));
	/*if (ok == false)
	{
		QMessageBox::warning(this, "Eroare", "Pret invalid!");
	}
	else
	{
		populateList(srv.filtrare_pret(pret));
	}*/
}

void MyGUI::filtru_pret_gui_colorare()
{
	double pret = sliderFiltrarePret->value();
	populateList(srv.get_all());
	auto lista_med = srv.filtrare_pret(pret);
	model->colorare_filtru(lista_med);
	for (const auto& med : lista_med)
	{
		auto items = listaMed->findItems(QString::fromStdString(med.get_denumire()), Qt::MatchExactly);
		items[0]->setBackground(QColor("yellow"));
	
	}
	/*bool ok;
	auto pret = editFiltruPret->text().toDouble(&ok);
	if (ok == false)
	{
		QMessageBox::warning(this, "Eroare", "Pret invalid!");
	}
	else
	{
		populateList(srv.get_all());
		auto lista_med = srv.filtrare_pret(pret);
		for (const auto& med : lista_med)
		{
			auto items = listaMed->findItems(QString::fromStdString(med.get_denumire()), Qt::MatchExactly);
			items[0]->setBackground(QColor("yellow"));
		}
	}*/
}

void MyGUI::filtru_substanta_gui()
{
	auto substanta = editFiltruSubstanta->text().toStdString();
	if (substanta == "")
		QMessageBox::warning(this, "Eroare", "Camp filtrare vid!");
	else
		populateList(srv.filtrare_substanta(substanta));
}

void MyGUI::filtru_substanta_gui_colorare()
{
	auto substanta = editFiltruSubstanta->text().toStdString();
	if (substanta == "")
		QMessageBox::warning(this, "Eroare", "Camp filtrare vid!");
	else
	{
		
		populateList(srv.get_all());
		auto lista_med=srv.filtrare_substanta(substanta);
		// pt model
		model->colorare_filtru(lista_med);
		for (const auto& med : lista_med)
		{
			auto items = listaMed->findItems(QString::fromStdString(med.get_denumire()), Qt::MatchExactly);
			items[0]->setBackground(QColor("purple"));
		}
	}
}

void MyGUI::raport_gui()
{
	auto dict = srv.numarMedicamenteProducator();
	//tabel_raport->clear();
	tabel_raport->setRowCount(0);
	for (const auto& item : dict)
	{
		auto producator = item.first;
		auto nr_med = item.second.get_nr_medic();
		QTableWidgetItem* titem1 = new QTableWidgetItem{ QString::fromStdString(producator) };
		QTableWidgetItem* titem2 = new QTableWidgetItem{ QString::number(nr_med) };
		tabel_raport->insertRow(tabel_raport->rowCount());
		tabel_raport->setItem(tabel_raport->rowCount() - 1, 0, titem1);
		tabel_raport->setItem(tabel_raport->rowCount() - 1, 1, titem2);
	}
	raport->show();

}

// functii pt reteta din main window
void MyGUI::add_reteta_gui()
{
	auto denumire = comboAdauga->currentText().toStdString();
	if (denumire == "")
		QMessageBox::warning(this, "Eroare", "Camp denumire vid!");
	else
	{
		try
		{
			srv.adauga_reteta(denumire);
		}
		catch (const RepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
		}
	}
}
void MyGUI::goleste_reteta_gui()
{
	srv.goleste_reteta();
}
void MyGUI::export_reteta_gui()
{
	auto nume_fis = editExport->text().toStdString();
	if (nume_fis == "")
		QMessageBox::warning(this, "Eroare", "Camp vid! Introdu un nume de fisier!");
	else
		srv.exporta(nume_fis);
}
void MyGUI::genereaza_reteta_gui()
{
	auto nr = spinGenereaza->value();
	try
	{
		srv.genereaza_reteta(nr);
	}
	catch (const RepoException& ex)
	{
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
	}
	/*bool ok;
	auto nr = editGenereaza->text().toInt(&ok);
	if (ok == false)
	{
		QMessageBox::warning(this, "Eroare", "Numar invalid!");
	}
	else
	{
		try
		{
			srv.genereaza_reteta(nr);
		}
		catch (const RepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
		}

	}*/
}


// pentru reteta
void RetetaGUI::initRetetaComp()
{
	this->setWindowTitle("Reteta");
	QVBoxLayout* main_main_ly = new QVBoxLayout;
	this->setLayout(main_main_ly);
	QHBoxLayout* main_ly = new QHBoxLayout;
	main_ly->addWidget(listaReteta);
	QVBoxLayout* butoane_ly = new QVBoxLayout;
	butoane_ly->addWidget(btnExit);
	butoane_ly->addWidget(btnRefresh);
	butoane_ly->addWidget(btnGoleste);
	QFormLayout* form_ly = new QFormLayout;
	form_ly->addRow(btnAdaugaReteta,comboAdauga);
	form_ly->addRow(btnGenereaza, editGenereaza);
	form_ly->addRow(btnExport, editExport);
	butoane_ly->addLayout(form_ly);
	main_ly->addLayout(butoane_ly);
	main_main_ly->addLayout(main_ly);
	QFormLayout* numarmed_ly = new QFormLayout;
	numarmed_ly->addRow("Numar medicamente:",label);
	main_main_ly->addLayout(numarmed_ly);
}
void RetetaGUI::initRetetaSignals()
{
	QObject::connect(btnExit, &QPushButton::clicked, this, [=]() {
		QMessageBox::information(this, "Exit", "Adieu!");
		// close inchide fereastra QWidget
		close();
		});
	QObject::connect(btnGoleste, &QPushButton::clicked, this, [=]() {
		reteta.goleste_reteta();
		populateReteta(reteta.get_reteta());
		});
	QObject::connect(btnAdaugaReteta, &QPushButton::clicked, this, &RetetaGUI::adauga_reteta_gui);
	QObject::connect(btnGenereaza, &QPushButton::clicked, this, &RetetaGUI::genereaza_reteta_gui);
	QObject::connect(btnExport, &QPushButton::clicked, this, &RetetaGUI::exporta_reteta_gui);
	QObject::connect(btnRefresh, &QPushButton::clicked, this, [=]() {
		editAdauga->setText("");
		editExport->setText("");
		editGenereaza->setText("");
		populateComboBox();
		reteta.notify();
		});
}

void RetetaGUI::populateComboBox()
{
	comboAdauga->clear();
	auto lista_med = reteta.get_all();
	for (const auto& med : lista_med)
	{
		auto denumire = med.get_denumire();
		comboAdauga->addItem(QString::fromStdString(denumire));
	}
}
void RetetaGUI::initialStateReteta()
{
	listaReteta->clear();
	populateReteta(reteta.get_reteta());
}

void RetetaGUI::populateReteta(const vector<Medicament>&lista_med)
{
	listaReteta->clear();
	for (const Medicament& med : lista_med)
	{
		auto denumire = med.get_denumire();
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(denumire) };
		listaReteta->addItem(item);
	}
	updateNumarMed();
	populateComboBox();
}

void RetetaGUI::adauga_reteta_gui()
{
	auto denumire = comboAdauga->currentText().toStdString();
	if (denumire == "")
		QMessageBox::warning(this, "Eroare", "Camp denumire vid!");
	else
	{
		try
		{
			reteta.adauga_reteta(denumire);
			populateReteta(reteta.get_reteta());
		}
		catch (const RepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
		}
	}
}
void RetetaGUI::genereaza_reteta_gui()
{
	bool ok;
	auto nr = editGenereaza->text().toInt(&ok);
	if (ok == false)
	{
		QMessageBox::warning(this, "Eroare", "Numar invalid!");
	}
	else
	{
		try
		{
			reteta.genereaza_reteta(nr);
			populateReteta(reteta.get_reteta());
		}
		catch (const RepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.get_mesaj()));
		}
		
	}
	
}
void RetetaGUI::exporta_reteta_gui()
{
	auto nume_fis = editExport->text().toStdString();
	if (nume_fis == "")
		QMessageBox::warning(this, "Eroare", "Camp vid! Introdu un nume de fisier!");
	else
		reteta.exporta(nume_fis);
}
void RetetaGUI::updateNumarMed()
{
	auto n = reteta.dimensiune_reteta();
	label->setText(QString::number(n));
}

// pentru QTableModel


int MyTableModel::rowCount(const QModelIndex& /*parent */) const
{
	return static_cast<unsigned int>(medicamente.size());
}

int MyTableModel::columnCount(const QModelIndex& /*parent*/ ) const
{
	return 4;
}

QVariant MyTableModel::data(const QModelIndex& index, int role ) const
{
	if (role == Qt::ForegroundRole)
	{
		Medicament med = medicamente[index.row()];
		if (med.get_pret() > 500)
		{
			return QBrush(Qt::red);
		}
	}

	if (role == Qt::DisplayRole)
	{
		qDebug() << "row: " << index.row() << "\n";
		Medicament med = medicamente[index.row()];
		if (index.column() == 0)
			return QString::fromStdString(med.get_denumire());
		else if (index.column() == 1)
			return QString::number(med.get_pret());
		else if (index.column() == 2)
			return QString::fromStdString(med.get_producator());
		else if (index.column() == 3)
			return QString::fromStdString(med.get_substanta());
	}

	if (role == Qt::BackgroundRole)
	{
		Medicament med = medicamente[index.row()];
		if (find_if(filtru.begin(), filtru.end(), [med](const Medicament& med1) {return med.get_denumire()==med1.get_denumire();}) != filtru.end())
			return QBrush(Qt::yellow);
	}

	if (role == Qt::UserRole)
	{
		Medicament med = medicamente[index.row()];
		return QString::fromStdString(med.get_denumire());
	}
	
	return QVariant{};
}

void MyTableModel::setMeds(const vector<Medicament>&meds)
{
	this->medicamente = meds;
	/*auto stangasus = createIndex(0, 0);
	auto dreaptajos = createIndex(rowCount()+1, columnCount());
	emit dataChanged(stangasus, dreaptajos);*/
	emit layoutChanged();
}

void MyTableModel::colorare_filtru(const vector<Medicament>meds)
{
	this->filtru = meds;
	emit layoutChanged();
	
}

void MyGUI::reloadList(const vector<Medicament>&lista_med)
{
	model->setMeds(lista_med);
	
}