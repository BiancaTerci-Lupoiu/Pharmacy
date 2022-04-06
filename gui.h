#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include<QtWidgets/qcombobox.h>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qboxlayout.h>
#include<qpainter.h>
#include "service.h"
#include "Observer.h"
#include "reteta.h"
#include <time.h>
#include<qslider.h>
#include<qspinbox.h>

class RetetaReadOnlyGUI :public QWidget, public Observer
{
private:
	Reteta& reteta;
public:
	RetetaReadOnlyGUI(Reteta& reteta) :reteta{ reteta } {
		reteta.addObserver(this);
		setFixedWidth(400);
		setFixedHeight(400);
	}

	void update() override {
		repaint();
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		//srand(time(NULL));
		const size_t n = reteta.get_reteta().size();
			for (int i = 0; i < n;i++) 
			{
			int x = rand()%380;
			int y = rand()%380;
			p.drawImage(x, y, QImage("img.png"));
			
		}
		// apare eroare daca nu folosesc ev
		ev = 0;
	}

};

// RetetaGUIcrud
class RetetaGUI : public QWidget,public Observer
{
private:
	Reteta& reteta;
	QListWidget* listaReteta = new QListWidget;
	QPushButton* btnAdaugaReteta = new QPushButton{ "Adauga" };
	QPushButton* btnGenereaza = new QPushButton{"Genereaza"};
	QPushButton* btnGoleste = new QPushButton{ "Goleste" };
	QPushButton* btnExport = new QPushButton{ "Export" };
	QPushButton* btnExit = new QPushButton{ "Exit" };
	QPushButton* btnRefresh = new QPushButton{ "Refresh" };

	QLineEdit* editAdauga = new QLineEdit;
	QLineEdit* editGenereaza = new QLineEdit;
	QLineEdit* editExport = new QLineEdit;
	QLineEdit* editNumarMed = new QLineEdit;
	QLabel* label = new QLabel{ "0" };

	QComboBox* comboAdauga = new QComboBox;

	void initRetetaComp();
	void initRetetaSignals();
	void initialStateReteta();
	void populateReteta(const vector<Medicament>&lista_med);
	void updateNumarMed();
	void populateComboBox();
public:
	RetetaGUI(Reteta& reteta) :reteta{ reteta } {
		reteta.addObserver(this);
		initRetetaComp();
		initRetetaSignals();
		initialStateReteta();
	}
	void adauga_reteta_gui();
	void genereaza_reteta_gui();
	void exporta_reteta_gui();
	void update() override {
		populateReteta(reteta.get_reteta());
	}
	// trebuie sa am si destructorul care apeleaza removeobserver
	~RetetaGUI() {
		reteta.removeObserver(this);
	}
	//friend class Reteta;
};

// Model pentru TableView
class MyTableModel : public QAbstractTableModel
{
private:
	vector<Medicament> medicamente;
	vector<Medicament> filtru;
public:
	MyTableModel(const vector<Medicament>& meds) :medicamente{ meds } {

	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setMeds(const vector<Medicament>&meds);

	void colorare_filtru(const vector<Medicament>meds);
};


class MyGUI :public QWidget
{
private:
	ServiceMedicamente& srv;
	QListWidget* listaMed = new QListWidget;
	QTableWidget* tabel = new QTableWidget{ 0,1 };
	QPushButton* btnSortDenumire = new QPushButton{ "Sortare Denumire" };
	QPushButton* btnSortProducator = new QPushButton{ "Sortare Producator" };
	QPushButton* btnSortSubstantaP = new QPushButton{ "Sortare Substanta+Pret" };
	QPushButton* btnRefresh = new QPushButton{ "Refresh" };
	QPushButton* btnExit = new QPushButton{ "Exit" };
	QPushButton* btnUndo = new QPushButton{ "Undo" };
	QPushButton* btnAdauga = new QPushButton{ "Adauga" };
	QPushButton* btnModifica = new QPushButton{ "Modifica" };
	QPushButton* btnSterge = new QPushButton{ "Sterge" };

	QPushButton* btnCauta = new QPushButton{ "Cauta" };
	QPushButton* btnFiltruPret = new QPushButton{ "Filtrare pret" };
	QPushButton* btnFiltruSubstanta = new QPushButton{ "Filtrare substanta" };

	QLineEdit* editCauta = new QLineEdit;
	//QLineEdit* editFiltruPret = new QLineEdit;
	QLineEdit* editFiltruSubstanta = new QLineEdit;

	QLineEdit* editDenumire=new QLineEdit;
	//QLineEdit* editPret=new QLineEdit;
	QLineEdit* editProducator = new QLineEdit;
	QLineEdit* editSubstanta = new QLineEdit;

	// componente pentru reteta
	//RetetaGUI* reteta = new RetetaGUI{ srv };
	QPushButton* btnReteta = new QPushButton{ "Reteta-crud" };
	QPushButton* btnRetetaRead = new QPushButton{ "Reteta-desenare" };
	QLabel* infoReteta = new QLabel{ "Operatii pe reteta" };
	QPushButton* btnAdaugaReteta = new QPushButton{ "Adauga" };
	QPushButton* btnGenereaza = new QPushButton{ "Genereaza" };
	QPushButton* btnGoleste = new QPushButton{ "Goleste" };
	QPushButton* btnExport = new QPushButton{ "Export" };
	QLineEdit* editAdauga = new QLineEdit;
	//QLineEdit* editGenereaza = new QLineEdit;
	QLineEdit* editExport = new QLineEdit;
	QComboBox* comboAdauga = new QComboBox;

	// raport
	QPushButton* btnRaport = new QPushButton{ "Raport" };
	QTableWidget* tabel_raport = new QTableWidget{ 0,2 };
	QWidget* raport = new QWidget;

	// slidere si spinbox
	QSlider* sliderFiltrarePret = new QSlider(Qt::Horizontal);
	QSpinBox* spinPret = new QSpinBox;
	QSpinBox* spinGenereaza = new QSpinBox;
	QLabel* labelslider = new QLabel;

	// pentru partea de butoane dinamice
	QVBoxLayout* lybtndin = new QVBoxLayout;

	// pentru tablemodelview
	QTableView* tableview = new QTableView;
	MyTableModel* model = new MyTableModel(srv.get_all());

	void initGUIComp();
	void initSignals();
	void initialState();
	void populateList(const vector<Medicament>&lista_med);
	void populateComboBox();

	//imi repopuleaza tableview dupa modificari
	void reloadList(const vector<Medicament>&lista_med);
	//friend class RetetaGUI;
public:
	MyGUI(ServiceMedicamente& serv) :srv{ serv } {
		initGUIComp();
		initSignals();
		initialState();
	}

	void adauga_gui();
	void modifica_gui();
	void sterge_gui();
	void undo_gui();
	void cauta_gui();
	void filtru_pret_gui();
	void filtru_pret_gui_colorare();
	void filtru_substanta_gui();
	void filtru_substanta_gui_colorare();
	void raport_gui();
	void show_reteta_crud();
	void show_reteta_read();
	void add_reteta_gui();
	void goleste_reteta_gui();
	void export_reteta_gui();
	void genereaza_reteta_gui();
	// pt fiecare producator apare cate un buton, daca se apasa butonul se sterg medicamentele de la acel producator
	void adauga_butoane_dinamic();
};



