#include "CosProduse.h"

//adauga un nou produs in cos
//input: - nume - string
//output: -, produsul a fost adaugat in cos
//arunca exceptie daca produsul nu exista in magazin
void RepoCos::addCos(const std::string& nume) {
	bool ok = false;
	Product cosP;
	for (const auto& p : repoProducts->getAll()) {
		if (p.getNume() == nume) {
			cosP = Product(p.getId(), p.getNume(), p.getProducator(), p.getTip(), p.getPret());
			allPinCos.push_back(cosP);
			ok = true;
		}
	}
	if (ok == false)
		throw RepoException("Nu exista nici un produs cu numele respectiv in cos!");
}

//goleste cosul de cumparaturi
//output: cosul este gol
void RepoCos::emptyCos() {
	allPinCos.clear();
}

//adauga produse random din magazin in cos
//input: nrProduse - integer - numarul de produse care trebuie adaugate in cos
//output: - produsele au fost adaugate in cos
void RepoCos::populateCos(const int& nrProduse) {

	std::vector<Product> allP = repoProducts->getAll();
	int i = 0;
	while (i < nrProduse) {
		std::random_device random_device;
		std::mt19937 engine{ random_device() };
		std::uniform_int_distribution<int> dist(0, allP.size() - 1);
		Product random_element = allP.at(dist(engine));

		allPinCos.push_back(random_element);
		++i;
	}
}

//modifica produsul, daca acesta exista in cos
//input: - p - Product - produsul modificat
//output: - produsul a fost adaugat
bool RepoCos::modificaElemente(const Product& p) {
	bool ok = false;
	for (auto& p1 : allPinCos) {
		if (p1.getId() == p.getId()) {
			ok = true;
			p1 = p;
		}
	}
	return ok;
}

//sterge o aparitie a produsului din cos
//input: id- integer -idul produsului ce trebuie sters
//output: true - produsul a fost sters cu succes
//        false produsul nu a fost gasit in cos
bool RepoCos::sterge(const int& id) {
	int poz = 0;

	while (poz < size()) {

		if (allPinCos.at(poz).getId() == id) {
			vector<Product>::iterator it;
			it = allPinCos.begin() + poz;
			this->allPinCos.erase(it);
			return true;
		}
		++poz;
	}
	return false;
}
//sterge produsul din cos
//input: - id- integer - idul produsului ce trebuie sters
//output: - produsul a fost sters
bool RepoCos::stergeElemente(const int& id) {
	bool ok = false;
	if (sterge(id) == true)
		ok = true;
	while (sterge(id) == true);

	return ok;
}

//returneaza numarul de elemente cu id-ul dat din cos
//input: id -integer
//output: nr - int - numarul de produse din cos care au id ul dat
int RepoCos::getNrId(const int& id) {
	int nr = 0;

	for (const auto& p : allPinCos) {
		if (p.getId() == id)
			nr++;
	}
	return nr;
}

//salveaza continutul cosului in fisier
//input: - fileName - string - numele fisierului
//output: - produsele din cos sunt salvate in fisier
void RepoCos::saveCos(std::string fileName) {
	std::ofstream g(fileName);
	g << "\"" << "ID" << "\",";
	g << "\"" << "NUME" << "\",";
	g << "\"" << "PRODUCATOR" << "\",";
	g << "\"" << "TIP" << "\",";
	g << "\"" << "PRET" << "\"";
	g << std::endl;
	for (const auto& p : allPinCos) {
		g << "\"" << p.getId() << "\",";
		g << "\"" << p.getNume() << "\",";
		g << "\"" << p.getProducator() << "\",";
		g << "\"" << p.getTip() << "\",";
		g << "\"" << p.getPret() << "\"";
		g << std::endl;
	}
	g << "Pretul total: " << pretTotal() << std::endl;
	g.close();
}

//returneaza o lista cu toate produsele din cos
const std::vector<Product>& RepoCos::getAllCos() {
	return allPinCos;
}

//returneaza pretul total al produselor din cos
//input:- 
//output: total - integer
int RepoCos::pretTotal() {
	int total = 0;
	for (const auto& p : allPinCos) {
		total = total + p.getPret();
	}
	return total;
}

//returneaza numarul de produse din cos
//input:-
//output: size -int
int RepoCos::size() const {
	return allPinCos.size();
}
