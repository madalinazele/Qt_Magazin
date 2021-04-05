#include "Service.h"

//destructor
Service::~Service() {
	int size = undoActions.size();
	while (size > 0) {
		ActiuneUndo* act = undoActions.back();
		undoActions.pop_back();
		delete act;
		--size;
	}
}

//adauga un Produs in magazin
//input: id,pret -int
//       nume, producator, tip - std:string
//       fileMode - int
//output: -, produsul este adaugat in magazin
//daca fileMode = 1 salveaza lista curenta de produse in fisier
//daca produsul exista deja in magazin, va arunca o eroare
void Service::addProduct(const int& id, const std::string& nume, const std::string& producator, const std::string& tip, const int& pret) {
	const Product& p = Product(id, nume, producator, tip, pret);
	val.validate(p);
	repo->add(p);
	undoActions.push_back(new UndoAdauga{ repo,cosRepository, p });

}

//modifica un produs din magazin
//input: id,pret -int
//       nume, producator, tip - stdd:string
//       fileMode - int
//output: -, produsul este modificat
//daca fileMode = 1 salveaza lista curenta de produse in fisier
//daca produsul nu exista in magazin, va arunca o eroare
void Service::updateProduct(const int& id, const std::string& nume, const std::string& producator, const std::string& tip, const int& pret) {
	Product p = Product(id, nume, producator, tip, pret);
	val.validate(p);
	try {
		Product pr = repo->findById(id);
		undoActions.push_back(new UndoModifica{ repo, cosRepository, pr });
	}
	catch (RepoException) {
	}
	repo->update(p);
	if (cosRepository.modificaElemente(p))
		notify();

}

//sterge produsul cu id ul respectiv din lista
//input: id - int
//       fileMode -int
//output: -, produsul este sters din lista
//daca fileMode = 1 salveaza lista curenta de produse in fisier
//arunca exceptie daca produsul nu se afla in magazin
void Service::removeProduct(const int& id) {
	try {
		int nr = cosRepository.getNrId(id);
		undoActions.push_back(new UndoSterge{ repo, cosRepository, repo->findById(id), nr });
	}
	catch (RepoException) {
	}
	repo->remove(id);
	if (cosRepository.stergeElemente(id))
		notify();

}

//returneaza o lista cu toate produsele
//input: -
//output: vector<Product>
vector<Product> Service::getAllProducts() noexcept {
	return repo->getAll();
}

//cauta elementul cu id ul dat in lista si il returneaza
//input: id- int
//output: Product - elementul cu id ul dat
//arunca exceptie daca elementul cu id ul dat nu exista in lista
const Product& Service::getProductById(const int& id) const {
	return repo->findById(id);
}

//returneaza numarul produselor din lista
//input: -
//outpur: int - lungimea listei
int Service::ListSize() const noexcept {
	return repo->size();
}

//filtreaza produsele dupa pret si returneaza lungimea listei filtrate
//preconditie: listaFiltrare este goala
//input : listaFiltare - lista de produse
//        pret1, pret2 - int
//output: len -int - numarul elementelor a caror pret se incadreaza intre cele 2 preturi date
//        listaFiltrare - lista de produse
//lista va contine toate produsele a caror pret se afla intre cele doua preturi date
int Service::filtrarePret(vector<Product>& listaFiltrare, const int& pret1, const int& pret2) {
	vector<Product> allP = repo->getAll();
	std::copy_if(allP.begin(), allP.end(), back_inserter(listaFiltrare), [pret1, pret2](Product p) {return (p.getPret() >= pret1 && p.getPret() <= pret2);  });


	return listaFiltrare.size();
}

//filtreaza elementele dupa nume
//input: listaFiltrare - lista care va contine Produsele ce respecta criteriile
//       sNume - stringul dupa care se face filtrarea
//ouput: len - lungimea listei filtrate
//       listaFiltrare - lista de produse - va contine produsele a caror nume contin stringul dat
int Service::filtrareNume(vector<Product>& listaFiltrare, const std::string& sNume) {
	vector<Product> allP = repo->getAll();
	std::copy_if(allP.begin(), allP.end(), back_inserter(listaFiltrare), [sNume](Product p) {return p.getNume().find(sNume) != std::string::npos; });
	/*for (const auto& p : repo->getAll()) {
		if (p.getNume().find(sNume) != std::string::npos) {
			listaFiltrare.push_back(p);
			++len;
		}
	}*/
	return listaFiltrare.size();
}

//filtreaza elementele dupa producator
//input: listaFiltrare - lista care va contine Produsele ce respecta criteriile
//       sProducator - stringul dupa care se face filtrarea
//ouput: len - lungimea listei filtrate
//       listaFiltrare - lista de produse - va contine produsele a caror producator contin stringul dat
int Service::filtrareProducator(vector<Product>& listaFiltrare, const std::string& sProducator) {
	vector<Product> allP = repo->getAll();
	std::copy_if(allP.begin(), allP.end(), back_inserter(listaFiltrare), [sProducator](Product p) {return p.getProducator().find(sProducator) != std::string::npos; });
	return listaFiltrare.size();
}

//face o copie a listei de produse din magazin
//input: copy -vector -lista de produse
//output: copy - va contine toate produsele din magazin
void Service::copyList(vector<Product>& copy) {

	for (const auto& p : repo->getAll()) {
		copy.push_back(p);
	}
}


//sorteaza produsele din lista dupa nume
//input: listaSortare - lista care va contine Produsele in ordinea lexicografica a numelui
//ouput: listaFiltrare - lista de produse - va contine produsele din magazin ordonate crescator dupa nume
void Service::sortareNume(vector<Product>& listaSortare) {
	int size;
	Product p1, p2, aux;
	size = repo->size();

	sort(listaSortare.begin(), listaSortare.end(), cmpNume);

	/*for (int i = 0; i < size - 1; ++i) {
		for (int j = i + 1; j < size; ++j) {
			p1 = listaSortare[i];
			p2 = listaSortare[j];
			if (p1.getNume() > p2.getNume()) {
				aux = listaSortare[i];
				listaSortare[i] = listaSortare[j];
				listaSortare[j] = aux;
			}
		}
	}*/
}

//sorteaza produsele din lista dupa pret
//input: listaSortare - lista care va contine Produsele in ordinea crescatoare a pretului
//ouput: listaFiltrare - lista de produse - va contine produsele din magazin ordonate crescator dupa pret
void Service::sortarePret(vector<Product>& listaSortare) {
	int size;
	Product aux;
	size = repo->size();

	sort(listaSortare.begin(), listaSortare.end(), cmpPret);
}

//sorteaza produsele din lista dupa nume+tip
//input: listaSortare - lista care va contine Produsele in ordinea lexicografica a numelui si a tipului
//ouput: listaFiltrare - lista de produse -
//       va contine produsele din magazin ordonate crescator dupa nume, iar daca numele sunt egale, se va ordona crescator dupa tip
void Service::sortareNumeTip(vector<Product>& listaSortare) {
	int size;
	Product p1, p2, aux;
	size = repo->size();

	sort(listaSortare.begin(), listaSortare.end(), cmpNumeTip);

}

//returneaza pretul total al produselor din magazin
//input: -
//output: integer
int Service::pretAcumulat() {
	vector<Product> vect = repo->getAll();
	return accumulate(vect.begin(), vect.end(), 0, [](int x, Product a) {return x + a.getPret(); });
}

//undo, reface ultima operatie efectuata
//input: - fileMode -int
//output: - lista de produse revine la forma de dinaintea ultimei operatii de adauga/sterge/modifica
//daca fileMode = 1 salveaza lista curenta de produse in fisier
//arunca exceptie daca nu mai exista operatii ce pot fi refacute
void Service::undo() {
	if (undoActions.empty())
		throw RepoException("Nu mai exista operatii ce pot fi refacute!");
	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
	notify();
}

//adauga un produs in cos
//input: - nume -string 
//ouput: produsul a fost adaugat
//arunca exceptie daca produsul nu exista in magazin
void Service::adaugaCos(const string& nume) {
	cosRepository.addCos(nume);

	undoActions.push_back(new UndoAdaugaCos{ repo,cosRepository, nume });
	notify();
}

//goleste cosul de cumparaturi
//output: cosul este gol
void Service::emptyCosP() {
	cosRepository.emptyCos();
	notify();
}
//adauga produse random din magazin in cos
//input: nrProduse - integer - numarul de produse care trebuie adaugate in cos
//output: - produsele au fost adaugate in cos
void Service::populateCosP(const int& nrProduse) {
	cosRepository.populateCos(nrProduse);
	notify();
}

//salveaza continutul cosului in fisier
//input: - fileName - string - numele fisierului
//output: - produsele din cos sunt salvate in fisier
void Service::saveToFile(const string& fileName) {
	cosRepository.saveCos(fileName);
}

//returneaza toate produsele din cos
const vector<Product>& Service::getAllProductsCos() {
	return cosRepository.getAllCos();
}

//returneaza pretul total al produselor din cos
//input:- 
//output: total - integer
int Service::pretTotalCos() {
	return cosRepository.pretTotal();
	//notify();
}

//returneaza numarul de produse din cos
//input:-
//output: size -int
int Service::sizeCos() const {
	return cosRepository.size();
}

//returneaza un raport cu tipul produselor din magazin
//pentru fiecare produs va fi specificat cate produse de acelasi tip exista in magazin
std::vector<EntityCountDTO> Service::raportTip() {
	std::vector<EntityCountDTO> lista;
	map<string, EntityCountDTO> dictionar;
	for (auto p : repo->getAll()) {
		const int a = dictionar.count(p.getTip());
		if (a == 1) {
			dictionar[p.getTip()].incCount();
		}
		else {
			EntityCountDTO e("", "", 1);
			dictionar.insert(pair<string, EntityCountDTO>(p.getTip(), e));
		}
	}

	for (auto p : repo->getAll()) {
		EntityCountDTO e(p.getNume(), p.getTip(), dictionar[p.getTip()].getCountDTO());
		lista.push_back(e);
	}
	return lista;

}