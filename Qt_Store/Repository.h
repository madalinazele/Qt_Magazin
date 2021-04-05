#pragma once
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <map>
#include <time.h>
#include <exception>
#include "Domain.h"

using namespace std;

class RepoAbstract {
public:
	virtual void add(const Product& p) = 0;

	virtual void update(const Product& p) = 0;

	virtual void remove(const int& idP) = 0;

	virtual vector<Product> getAll() noexcept = 0;

	virtual const Product& findById(const int& idP) const = 0;

	virtual int size() const noexcept = 0;

	virtual ~RepoAbstract() {};
};


class Repository : public RepoAbstract {
private:
	vector<Product> productList;

public:

	//constructor
	Repository() = default;

	Repository(const Repository& rep) = delete;

	//adauga un nou produs in magazin
	//arunca exceptie daca produsul exista deja
	void add(const Product& p) override;

	//sterge un produs din magazin
	//arunca exceptie daca nu exista produsul respectiv in magazin
	void remove(const int& id1) override;

	//modifica un produs din magazin
	//arunca exceptie daca nu exista produsul respectiv in stoc
	void update(const Product& p) override;

	//returneaza toate produsele din magazin
	vector<Product> getAll() noexcept override;

	//returneaza elementul cu id ul dat
	//arunca eroare daca elementul nu exista
	const Product& findById(const int& id1) const;

	//returneaza numarul de produse din magazin
	int size() const noexcept;
};


class RepoFile : public RepoAbstract {
private:
	string numeFisier;
	vector<Product> productList;
	void loadFromFile();
	void writeToFile();

public:
	//constructor
	RepoFile(const string& nume) : numeFisier{ nume } {
		this->loadFromFile();
	}

	//adauga un nou produs in magazin
	//arunca exceptie daca produsul exista deja
	void add(const Product& p) override;

	//sterge un produs din magazin
	//arunca exceptie daca nu exista produsul respectiv in magazin
	void remove(const int& id1) override;

	//modifica un produs din magazin
	//arunca exceptie daca nu exista produsul respectiv in stoc
	void update(const Product& p) override;

	//returneaza toate produsele din magazin
	vector<Product> getAll() noexcept override;

	//returneaza elementul cu id ul dat
	//arunca eroare daca elementul nu exista
	const Product& findById(const int& id1) const;

	//returneaza numarul de produse din lista
	int size() const noexcept;

};

//clasa de exceptii pt repository
class RepoException {
	std::string msg;
public:
	RepoException(std::string m) : msg{ m } {};

	friend std::ostream& operator<<(std::ostream& out, const RepoException& error);
};

//clasa repo - probabilitati
class RepoNou : public RepoAbstract {
private:
	float procent;
	vector<Product> productList;

public:

	RepoNou(float pr) : procent{ pr } {
		procent *= 100;
		srand(static_cast<unsigned int>(time(nullptr)));
		if (rand() % 20 >= procent)
			throw RepoException("Probabilitate!");
	}

	//adauga un nou produs in magazin
	//arunca exceptie daca produsul exista deja
	void add(const Product& p) override;

	//sterge un produs din magazin
	//arunca exceptie daca nu exista produsul respectiv in magazin
	void remove(const int& id1) override;

	//modifica un produs din magazin
	//arunca exceptie daca nu exista produsul respectiv in stoc
	void update(const Product& p) override;

	//returneaza toate produsele din magazin
	vector<Product> getAll() noexcept override;

	//returneaza elementul cu id ul dat
	//arunca eroare daca elementul nu exista
	const Product& findById(const int& id1) const;

	//returneaza numarul de produse din magazin
	int size() const noexcept;
};

