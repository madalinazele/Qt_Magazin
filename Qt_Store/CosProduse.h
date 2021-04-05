#pragma once
#include "Repository.h"

class RepoCos {
private:
	vector<Product> allPinCos;
	RepoAbstract* repoProducts;
public:
	//constructor
	RepoCos(RepoAbstract* repo) : repoProducts{ repo } {};

	//adauga un produs din magazin in cos
	//arunca exceptie daca produsul respectiv nu exista in magazin
	void addCos(const std::string& nume);

	//goleste cosul de cumparaturi
	void emptyCos();

	//calculeaza pretul total al produselor din cos
	int pretTotal();

	//adauga produse random din magazin in cosul de cumparaturi
	void populateCos(const int& nrProduse);

	//modifica produsul daca acesta exista in cos
	bool modificaElemente(const Product& p);

	//sterge o aparitie a produsului din cos
	//returneaza true daca produsul a fost sters cu succes si false daca acesta nu a fost gasit in cos
	bool sterge(const int& id);

	//sterge produsul din cos daca acesta exista
	bool stergeElemente(const int& id);

	//returneaza numarul de elemente de acelasi tip din cos
	int getNrId(const int& id);

	//salveaza continutul cosului intr-un fisier
	void saveCos(string fileName);

	//returneaza toate produsele din cos
	const vector<Product>& getAllCos();

	//returneaza numarul de produse din cos
	int size() const;
};