#include "Validator.h"

void Validator::validate(const Product& p) {
	vector<string> msg;
	if (p.getPret() < 0)
		msg.push_back("Pret negativ!!!");
	if (p.getId() < 0)
		msg.push_back("Id negativ!!!");
	if (p.getNume().size() == 0)
		msg.push_back("Nume vid!!!");
	if (p.getProducator().size() == 0)
		msg.push_back("Producator vid!!!");
	if (p.getTip().size() == 0)
		msg.push_back("Tip vid!!!");

	if (msg.size() > 0)
		throw ValidateException(msg);
}