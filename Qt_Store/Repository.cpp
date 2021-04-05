#include "Repository.h"

//adauga un nou produs in lista
//input: p - Product - produsul ce trebuie adaugat
//output: -, produsul este adaugat in lista
//arunca exceptie daca produsul exista deja in lista
void Repository::add(const Product& p) {
	for (auto& el : productList) {
		if (el.getId() == p.getId())
			throw RepoException("Produsul exista deja in lista");
	}
	this->productList.push_back(p);
}

//modifica un produs din lista
//input: p -Product - produsul modificat
//output: -, produsl este modificat
//arunca exceptie daca produsul nu exista in lista
void Repository::update(const Product& p) {
	bool found = false;
	for (auto& el : productList) {
		if (el.getId() == p.getId())
		{
			//remove(p.getId());
			//add(p);
			el = p;
			found = true;
			break;
		}
	}
	if (!found)
		throw RepoException("Nu exista produsul in lista!");
}

//sterge un element din lista
//input: id- integer - id-ul produsului ce trebuie sters
//output: -, produsul va fi sters din lista
//arunca exceptie daca produsul nu se afla in lista
void Repository::remove(const int& idP) {
	bool found = false;
	int poz = 0;

	while (poz < size()) {

		if (productList.at(poz).getId() == idP) {
			vector<Product>::iterator it;
			it = productList.begin() + poz;
			this->productList.erase(it);
			found = true;
			break;
		}
		++poz;
	}
	if (!found)
		throw RepoException("Produsul nu exista!");
}

//returneaza lista elementelor din repository
//input: -
//output: list - vector<Product>
vector<Product> Repository::getAll() noexcept {
	//std::vector<Product> list;
	//transform(productList.begin(), productList.end(), back_inserter(list), [](std::pair<int, Product> const& pair) {return pair.second; });
	//return list;
	return this->productList;
}

//returneaza elementul cu id ul dat
//input: id - integer
//output: Product
//arunca exceptie daca nu exista elementul respectiv in lista
const Product& Repository::findById(const int& id1) const {
	for (const auto& p : productList) {
		if (p.getId() == id1)
			return p;
	}
	throw RepoException("Nu exista produsul cu id ul respectiv in stoc!");
}

//numarul de elemente din lista
int Repository::size() const noexcept {
	return productList.size();
}




//salveaza lista cu produse in fisier
//input: allP - vector<Product>
//output: lista a fost salvata in fisier
void RepoFile::writeToFile() {
	ofstream g(numeFisier);
	g.width(10);
	g << "ID";
	g.width(20);
	g << "NUME";
	g.width(20);
	g << "PRODUCATOR";
	g.width(20);
	g << "TIP";
	g.width(10);
	g << "PRET" << endl;

	for (const auto& p : productList) {
		g.width(10);
		g << p.getId();
		g.width(20);
		g << p.getNume();
		g.width(20);
		g << p.getProducator();
		g.width(20);
		g << p.getTip();
		g.width(10);
		g << p.getPret() << endl;
	}
	g.close();
}

//citeste lista cu produse din fisier
void RepoFile::loadFromFile() {
	ifstream f(this->numeFisier);
	if (!f.is_open()) {
		throw RepoException("Fisierul nu s-a putut deschide!");
	}
	int id = 0, pret = 0;
	string nume, prod, tip;
	char header[100];
	f.getline(header, 100);
	f.get();
	//productList.clear();
	f.clear();
	while (!f.eof()) {
		f >> id;
		if (f.fail())
			break;
		f >> nume >> prod >> tip >> pret;
		Product p(id, nume, prod, tip, pret);

		productList.push_back(p);
	}
	f.close();
}

//adauga un nou produs in lista
//input: p - Product - produsul ce trebuie adaugat
//output: -, produsul este adaugat in lista
//arunca exceptie daca produsul exista deja in lista
void RepoFile::add(const Product& p) {
	for (auto& el : productList) {
		if (el.getId() == p.getId())
			throw RepoException("Produsul exista deja in lista");
	}
	this->productList.push_back(p);
	writeToFile();
}

//modifica un produs din lista
//input: p -Product - produsul modificat
//output: -, produsl este modificat
//arunca exceptie daca produsul nu exista in lista
void RepoFile::update(const Product& p) {
	bool found = false;
	for (auto& el : productList) {
		if (el.getId() == p.getId())
		{
			//remove(p.getId());
			//add(p);
			el = p;
			found = true;
			break;
		}
	}
	if (!found)
		throw RepoException("Nu exista produsul in lista!");
	writeToFile();
}

//sterge un element din lista
//input: id- integer - id-ul produsului ce trebuie sters
//output: -, produsul va fi sters din lista
//arunca exceptie daca produsul nu se afla in lista
void RepoFile::remove(const int& idP) {
	bool found = false;
	int poz = 0;

	while (poz < size()) {

		if (productList.at(poz).getId() == idP) {
			vector<Product>::iterator it;
			it = productList.begin() + poz;
			this->productList.erase(it);
			found = true;
			break;
		}
		++poz;
	}
	if (!found)
		throw RepoException("Produsul nu exista!");
	writeToFile();
}

//returneaza lista elementelor din repository
//input: -
//output: list - vector<Product>
vector<Product> RepoFile::getAll() noexcept {
	//std::vector<Product> list;
	//transform(productList.begin(), productList.end(), back_inserter(list), [](const Product& p) {return p; });
	//return list;
	return this->productList;
}

//returneaza elementul cu id ul dat
//input: id - integer
//output: Product
//arunca exceptie daca nu exista elementul respectiv in lista
const Product& RepoFile::findById(const int& id1) const {
	for (const auto& p : productList) {
		if (p.getId() == id1)
			return p;
	}
	throw RepoException("Nu exista produsul cu id ul respectiv in stoc!");
}

//numarul de elemente din lista
int RepoFile::size() const noexcept {
	return productList.size();
}





void RepoNou::add(const Product& p) {
	if (rand() % 100 >= procent) throw RepoException("Probabilitate!");
	for (auto& el : productList) {
		if (el.getId() == p.getId())
			throw RepoException("Produsul exista deja in lista");
	}
	this->productList.push_back(p);
}

void RepoNou::remove(const int& idP) {
	if (rand() % 100 >= procent) throw RepoException("Probabilitate!");
	bool found = false;
	int poz = 0;

	while (poz < size()) {

		if (productList.at(poz).getId() == idP) {
			vector<Product>::iterator it;
			it = productList.begin() + poz;
			this->productList.erase(it);
			found = true;
			break;
		}
		++poz;
	}
	if (!found)
		throw RepoException("Produsul nu exista!");
}

void RepoNou::update(const Product& p) {
	if (rand() % 100 >= procent) throw RepoException("Probabilitate!");

	bool found = false;
	for (auto& el : productList) {
		if (el.getId() == p.getId())
		{
			el = p;
			found = true;
			break;
		}
	}
	if (!found)
		throw RepoException("Nu exista produsul in lista!");
}

//returneaza lista elementelor din repository
//input: -
//output: list - vector<Product>
vector<Product> RepoNou::getAll() noexcept {
	//std::vector<Product> list;
	//transform(productList.begin(), productList.end(), back_inserter(list), [](const Product& p) {return p; });
	//return list;
	return this->productList;
}

//returneaza elementul cu id ul dat
//input: id - integer
//output: Product
//arunca exceptie daca nu exista elementul respectiv in lista
const Product& RepoNou::findById(const int& id1) const {
	for (const auto& p : productList) {
		if (p.getId() == id1)
			return p;
	}
	throw RepoException("Nu exista produsul cu id ul respectiv in stoc!");
}

//numarul de elemente din lista
int RepoNou::size() const noexcept {
	return productList.size();
}