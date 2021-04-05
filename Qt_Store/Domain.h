#pragma once
#include <string>
#include <iostream>

class Product {
private:
	int id = 0;
	std::string nume;
	std::string tip;
	int pret = 0;
	std::string producator;

public:
	//constructor default
	Product() = default;

	//constructor,creeaza un nou produs
	Product(const int& id, const std::string& nume, const std::string& producator, const std::string& tip, const int& pret);

	//returneaza id ul produsului
	int getId() const noexcept {
		return this->id;
	}

	//returneaza numele produsului
	std::string getNume() const {
		return this->nume;
	}

	//returneaza producatorul produsului
	std::string getProducator() const {
		return this->producator;
	}

	//returneaza tipul produsului
	std::string getTip() const {
		return this->tip;
	}

	//returneaza pretul produsului
	int getPret()const noexcept {
		return this->pret;
	}
};

bool cmpNume(const Product& p1, const Product& p2);

bool cmpPret(const Product& p1, const Product& p2);

bool cmpNumeTip(const Product& p1, const Product& p2);
