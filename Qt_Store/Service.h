#pragma once
#include <algorithm>
#include <numeric>
#include "Repository.h"
#include "Validator.h"
#include "Undo.h"
#include "Observer.h"
class EntityCountDTO {
private:
	string nume;
	string tip;
	int count;
public:
	EntityCountDTO() = default;
	EntityCountDTO(const string& nume, const string& tip, int count) : nume{ nume }, tip{ tip }, count{ count } {};

	string getNumeDTO() { return this->nume; }
	string getTipDTO() { return this->tip; }
	int getCountDTO() { return this->count; }
	void incCount() { this->count++; }
};

class Service : public Observable {
private:
	RepoAbstract* repo;
	Validator& val;
	RepoCos& cosRepository;
	vector<ActiuneUndo*> undoActions;

public:

	//constructor
	Service(RepoAbstract* repository, Validator& valid, RepoCos& repoCos) : repo{ repository }, val{ valid }, cosRepository{ repoCos } {};

	//destructor
	~Service();

	//nu permitem copierea de obiecte Service
	Service(const Service& service) = delete;

	//adauga produs in magazin
	//arunca eroare daca produsul exista deja in magazin
	void addProduct(const int& id, const std::string& nume, const std::string& producator, const std::string& tip, const int& pret);

	//modifica produs
	//arunca eroare daca produsul nu exista in magazin
	void updateProduct(const int& id, const std::string& nume, const std::string& producator, const std::string& tip, const int& pret);

	//sterge produs
	//arunca eroare daca produsul nu exista in magazin
	void removeProduct(const int& id);

	//returneaza toate produsele din magazin
	vector<Product> getAllProducts() noexcept;

	//returneaza elementul cu id ul dat 
	//arunca eroare daca elementul nu exista
	const Product& getProductById(const int& id) const;

	//returneaza numarul de produse din magazin
	int ListSize() const noexcept;

	//filtreaza dupa pret
	int filtrarePret(vector<Product>& listaFiltrare, const int& pret1, const int& pret2);

	//filtreaza dupa nume
	int filtrareNume(vector<Product>& listaFiltrare, const std::string& sNume);

	//filtreaza dupa producator
	int filtrareProducator(vector<Product>& listaFiltrare, const std::string& sProducator);

	//creeaza o copie a listei de produse
	void copyList(vector<Product>& copy);

	//sorteaza dupa nume
	void sortareNume(vector<Product>& listaSortare);

	//sorteaza dupa pret
	void sortarePret(vector<Product>& listaSortare);

	//sorteaza dupa nume si tip
	void sortareNumeTip(vector<Product>& listaSortare);

	//undo, reface ultima operatie de adauga/sterge/modifica
	void undo();

	//returneaza pretul total al produselor din magazin
	int pretAcumulat();

	//adauga un produs in cosul de cumparaturi
	//arunca exceptie daca produsul nu exista in magazin
	void adaugaCos(const string& nume);

	//goleste cosul de cumparaturi
	void emptyCosP();

	//adauga produse random din magazin in cos
	void populateCosP(const int& nrProduse);

	//salveaza continutul cosului intr-un fisier
	void saveToFile(const string& fileName);

	//returneaza toate produsele din cos
	const vector<Product>& getAllProductsCos();

	//returneaza pretul total al produselor din cos
	int pretTotalCos();

	//returneaza numarul de elemente din cos
	int sizeCos() const;

	//raport tip
	std::vector<EntityCountDTO> raportTip();
};


