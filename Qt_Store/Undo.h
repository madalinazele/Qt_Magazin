#pragma once
#include "Repository.h"
#include "CosProduse.h"

//clasa abstracta undo
class ActiuneUndo {
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() {};
};

//clasa de undo pentru adaugare
//sterge elementul adaugat
//daca a fost adaugat si in cos il sterge si din cos
class UndoAdauga : public ActiuneUndo {
private:
	Product produsAdaugat;
	RepoAbstract* repo;
	RepoCos& repoCos;
public:
	UndoAdauga(RepoAbstract* repository, RepoCos& repositoryCos, const Product& produs) : repo{ repository }, repoCos{ repositoryCos }, produsAdaugat{ produs } {}

	void doUndo() override {
		repo->remove(produsAdaugat.getId());
		repoCos.stergeElemente(produsAdaugat.getId());
	}
};

//clasa de undo pentru stergere
//adauga elemetul sters
//daca elementul a fost in cos inainte de a fi sters, il adauga
class UndoSterge : public ActiuneUndo {
private:
	Product produsSters;
	RepoAbstract* repo;
	RepoCos& repoCos;
	int nr;
public:
	UndoSterge(RepoAbstract* repository, RepoCos& repositoryCos, const Product& p, int n) : repo{ repository }, repoCos{ repositoryCos }, produsSters{ p }, nr{ n }{}

	void doUndo() override {
		repo->add(produsSters);
		while (nr > 0) {
			repoCos.addCos(produsSters.getNume());
			nr--;
		}
	}
};

//clasa de undo pentru modifica
//sterge modificarile facute produsului
//daca elementul este in cos, il modifica si acolo
class UndoModifica : public ActiuneUndo {
private:
	Product produsModificat;
	RepoAbstract* repo;
	RepoCos& repoCos;
public:
	UndoModifica(RepoAbstract* repository, RepoCos& repositoryCos, const Product& p) : repo{ repository }, repoCos{ repositoryCos }, produsModificat{ p } {}

	void doUndo() override {
		repo->update(produsModificat);
		repoCos.modificaElemente(produsModificat);
	}
};

class UndoAdaugaCos : public ActiuneUndo {
private:
	string nume;
	RepoAbstract* repo;
	RepoCos& repoCos;
public:
	UndoAdaugaCos(RepoAbstract* repository, RepoCos& repositoryCos, string n) : repo{ repository }, repoCos{ repositoryCos }, nume{ n } {}

	void doUndo() override {
		for (auto& p : repoCos.getAllCos()) {
			if (p.getNume() == nume)
			{
				repoCos.sterge(p.getId());
				break;
			}
		}

	}
};
