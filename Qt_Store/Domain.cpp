#include "Domain.h"


//constructor produs
Product::Product(const int& id, const std::string& nume, const std::string& producator, const std::string& tip, const int& pret)
	: id{ id }, nume{ nume }, producator{ producator }, tip{ tip }, pret{ pret } {
}

/*Product::Product(const Product& p) :id{ p.id }, nume{ p.nume }, producator{ p.producator }, tip{ p.tip }, pret{ p.pret } {
	std::cout << "Copy constructor used!\n";
}*/


//compara 2 elemente dupa nume
bool cmpNume(const Product& p1, const Product& p2) {
	return (p1.getNume() < p2.getNume());
}

//compara 2 elemente dupa pret
bool cmpPret(const Product& p1, const Product& p2) {
	return (p1.getPret() < p2.getPret());
}

//compara 2 elemente duoa nume+tip
bool cmpNumeTip(const Product& p1, const Product& p2) {
	if (p1.getNume() == p2.getNume()) {
		return (p1.getTip() < p2.getTip());
	}
	return p1.getNume() < p2.getNume();
}