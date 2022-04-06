#include "validator.h"
void Validator::valideaza(const Medicament& med)
{
	string erori;
	if (med.get_denumire().empty())
		erori += "Denumire invalida!\n";
	if (med.get_pret() <= 0)
		erori += "Pret invalid!\n";
	if (med.get_producator().empty())
		erori += "Producator invalid!\n";
	if (med.get_substanta().empty())
		erori += "Substanta invalida!\n";
	if (erori.size() > 0)
		throw ValidException(erori);
	return;

}
string ValidException::get_mesaj() const {
	return msg;
}