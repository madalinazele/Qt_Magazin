#include "Service.h"
#include "TestService.h"
#include <cassert>

void testAllService() {
	RepoAbstract* repo = new Repository;
	testAddProduct(repo);
	testUpdateProduct(repo);
	testRemoveProduct(repo);
	testFindById(repo);
	testFiltrarePret(repo);
	testFiltrareNume(repo);
	testFiltrareProducator(repo);
	testSortareNume(repo);
	testSortarePret(repo);
	testSortareNumeTip(repo);
	testDTO(repo);
	testUndo(repo);

	testAddCos(repo);
	testRemoveCos(repo);
	testUpdateCos(repo);
	testSaveCos(repo);
	delete repo;
}

void testAddProduct(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	try {
		srv.addProduct(1, "gem", "tara", "afine", 10);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		srv.addProduct(-5, "gem", "", "afine", 10);
	}
	catch (ValidateException&) {
		assert(true);
	}

	int size;
	size = srv.ListSize();
	vector<Product> all = srv.getAllProducts();
	assert(size == 2);
	assert(all[1].getPret() == 3);
	assert(all[0].getNume() == "ciocolata");
	assert(srv.pretAcumulat() == 7);

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testUpdateProduct(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	try {
		srv.updateProduct(5, "gem", "tara", "afine", 10);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		srv.updateProduct(1, "", "tara", "", 10);
	}
	catch (ValidateException&) {
		assert(true);
	}

	srv.updateProduct(2, "gem", "tara", "afine", 10);

	assert(srv.ListSize() == 2);
	assert(srv.getProductById(2).getPret() == 10);
	assert(srv.getProductById(2).getTip() == "afine");
	assert(srv.getProductById(1).getNume() == "ciocolata");

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testRemoveProduct(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	try {
		srv.removeProduct(5);
	}
	catch (RepoException&) {
		assert(true);
	}

	srv.removeProduct(1);

	assert(srv.ListSize() == 1);
	assert(srv.getProductById(2).getTip() == "vanilie");
	assert(srv.getProductById(2).getNume() == "napolitane");

	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
	//vector<Product> all = srv.getAllProducts();
}

void testFindById(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	try {
		srv.getProductById(5);
	}
	catch (RepoException&) {
		assert(true);
	}

	Product p1 = srv.getProductById(1);

	assert(srv.ListSize() == 2);
	assert(p1.getTip() == "alba");
	assert(p1.getNume() == "ciocolata");

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testFiltrarePret(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "gem", "tara", "afine", 10);

	vector<Product> listaFiltrare;
	int len = srv.filtrarePret(listaFiltrare, 2, 10);
	assert(len == 3);
	assert(listaFiltrare[0].getNume() == "ciocolata");
	assert(listaFiltrare[1].getProducator() == "alka");

	listaFiltrare.clear();

	len = srv.filtrarePret(listaFiltrare, 12, 15);
	assert(len == 0);

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

void testFiltrareNume(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "inghetata", "diany", "afine", 10);

	vector<Product> listaFiltrare;
	int len = srv.filtrareNume(listaFiltrare, "ata");
	assert(len == 2);
	assert(listaFiltrare[0].getNume() == "ciocolata");
	assert(listaFiltrare[1].getTip() == "afine");
	assert(listaFiltrare[1].getProducator() == "diany");

	listaFiltrare.clear();

	len = srv.filtrareNume(listaFiltrare, "napo");
	assert(len == 1);
	assert(listaFiltrare[0].getProducator() == "alka");

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

void testFiltrareProducator(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "inghetata", "milan", "afine", 10);

	vector<Product> listaFiltrare;
	int len = srv.filtrareProducator(listaFiltrare, "lka");
	assert(len == 2);
	assert(listaFiltrare[0].getNume() == "ciocolata");
	assert(listaFiltrare[1].getTip() == "vanilie");
	assert(listaFiltrare[1].getNume() == "napolitane");

	listaFiltrare.clear();

	len = srv.filtrareProducator(listaFiltrare, "boo");
	assert(len == 0);

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

void testSortareNume(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "inghetata", "milan", "afine", 10);

	vector<Product> listaSortare;
	srv.copyList(listaSortare);

	srv.sortareNume(listaSortare);
	assert(listaSortare.size() == 3);
	assert(listaSortare[0].getNume() == "ciocolata");
	assert(listaSortare[1].getTip() == "afine");
	assert(listaSortare[2].getNume() == "napolitane");

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

void testSortarePret(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "inghetata", "milan", "afine", 10);

	vector<Product> listaSortare;
	srv.copyList(listaSortare);

	srv.sortarePret(listaSortare);
	assert(listaSortare.size() == 3);
	assert(listaSortare[2].getNume() == "inghetata");
	assert(listaSortare[1].getTip() == "alba");
	assert(listaSortare[0].getNume() == "napolitane");

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

void testSortareNumeTip(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);

	srv.addProduct(1, "ciocolata", "milka", "migdale", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "ciocolata", "milka", "caramel", 10);

	vector<Product> listaSortare;
	srv.copyList(listaSortare);

	srv.sortareNumeTip(listaSortare);
	assert(listaSortare.size() == 3);
	assert(listaSortare[0].getTip() == "caramel");
	assert(listaSortare[1].getNume() == "ciocolata");
	assert(listaSortare[1].getTip() == "migdale");
	assert(listaSortare[2].getNume() == "napolitane");

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

void testAddCos(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);// , repoFile);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	srv.adaugaCos("ciocolata");
	srv.adaugaCos("napolitane");
	srv.adaugaCos("ciocolata");
	assert(srv.pretTotalCos() == 11);
	assert(srv.sizeCos() == 3);

	try {
		srv.adaugaCos("gem");
	}
	catch (RepoException&) {
		assert(true);
	}

	vector<Product> all = srv.getAllProductsCos();
	assert(all.at(0).getNume() == "ciocolata");
	assert(all.at(1).getProducator() == "alka");

	srv.emptyCosP();
	assert(srv.pretTotalCos() == 0);
	srv.populateCosP(10);
	assert(srv.sizeCos() == 10);

	srv.emptyCosP();
	assert(srv.sizeCos() == 0);

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testUpdateCos(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);// , repoFile);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	srv.adaugaCos("ciocolata");
	srv.adaugaCos("napolitane");
	srv.adaugaCos("ciocolata");
	assert(srv.pretTotalCos() == 11);
	assert(srv.sizeCos() == 3);

	srv.updateProduct(2, "gem", "tara", "afine", 10);

	assert(srv.sizeCos() == 3);
	std::vector<Product> allP = srv.getAllProductsCos();
	assert(allP.at(2).getPret() == 4);
	assert(allP.at(1).getTip() == "afine");
	assert(allP.at(1).getNume() == "gem");

	assert(srv.pretTotalCos() == 18);
	srv.emptyCosP();
	assert(srv.sizeCos() == 0);

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testRemoveCos(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);// , repoFile);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	srv.adaugaCos("ciocolata");
	srv.adaugaCos("napolitane");
	srv.adaugaCos("ciocolata");
	assert(srv.pretTotalCos() == 11);
	assert(srv.sizeCos() == 3);

	try {
		srv.removeProduct(5);
	}
	catch (RepoException&) {
		assert(true);
	}

	srv.removeProduct(2);

	assert(srv.sizeCos() == 2);
	std::vector<Product> allP = srv.getAllProductsCos();
	assert(allP.at(0).getPret() == 4);
	assert(allP.at(1).getTip() == "alba");
	assert(srv.pretTotalCos() == 8);

	srv.undo();
	assert(srv.sizeCos() == 3);
	assert(srv.pretTotalCos() == 11);

	srv.emptyCosP();
	assert(srv.sizeCos() == 0);

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testSaveCos(RepoAbstract* repo) {
	Validator val;
	RepoCos repoCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repoCos);//, repoFile);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);

	srv.populateCosP(5);
	assert(srv.sizeCos() == 5);
	srv.populateCosP(5);
	assert(srv.sizeCos() == 10);

	srv.saveToFile("testCos.csv");

	srv.emptyCosP();
	srv.saveToFile("testCos.csv");
	assert(srv.pretTotalCos() == 0);
	assert(srv.sizeCos() == 0);

	srv.removeProduct(1);
	srv.removeProduct(2);
	assert(srv.ListSize() == 0);
}

void testUndo(RepoAbstract* repo) {
	Validator val;
	RepoCos repCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repCos);// , repoFile);

	srv.addProduct(1, "ciocolata", "milka", "alba", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "inghetata", "milan", "afine", 10);

	srv.updateProduct(2, "napolitane", "alfers", "rom", 6);

	srv.removeProduct(1);

	srv.addProduct(4, "gem", "buni", "afine", 16);
	assert(srv.ListSize() == 3);

	srv.undo();
	assert(srv.ListSize() == 2);
	vector<Product> allP = srv.getAllProducts();
	assert(allP[0].getId() == 2);
	assert(allP[1].getNume() == "inghetata");
	assert(allP[0].getProducator() == "alfers");

	srv.undo();
	assert(srv.ListSize() == 3);
	allP = srv.getAllProducts();
	assert(allP[2].getId() == 1);
	assert(allP[1].getNume() == "inghetata");
	assert(allP[0].getProducator() == "alfers");
	assert(allP[2].getTip() == "alba");

	srv.undo();
	assert(srv.ListSize() == 3);
	allP = srv.getAllProducts();
	assert(allP[2].getId() == 1);
	assert(allP[1].getNume() == "inghetata");
	assert(allP[0].getProducator() == "alka");
	assert(allP[0].getTip() == "vanilie");

	srv.undo();
	assert(srv.ListSize() == 2);
	allP = srv.getAllProducts();
	assert(allP[1].getId() == 1);
	assert(allP[0].getProducator() == "alka");

	srv.adaugaCos("napolitane");
	assert(srv.sizeCos() == 1);
	srv.adaugaCos("ciocolata");
	assert(srv.sizeCos() == 2);
	srv.undo();
	assert(srv.sizeCos() == 1);
	srv.undo();
	assert(srv.sizeCos() == 0);

	srv.undo();
	assert(srv.ListSize() == 1);
	allP = srv.getAllProducts();
	assert(allP[0].getId() == 1);
	assert(allP[0].getProducator() == "milka");

	srv.undo();
	assert(srv.ListSize() == 0);

	try {
		srv.undo();
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testDTO(RepoAbstract* repo) {
	Validator val;
	RepoCos repCos(repo);
	//RepoFile repoFile("test.txt");
	Service srv(repo, val, repCos);// , repoFile);

	srv.addProduct(1, "ciocolata", "milka", "capsuni", 4);
	srv.addProduct(2, "napolitane", "alka", "vanilie", 3);
	srv.addProduct(3, "inghetata", "milan", "capsuni", 10);

	vector<EntityCountDTO> raportDTO = srv.raportTip();
	assert(raportDTO[0].getTipDTO() == "capsuni");
	assert(raportDTO[0].getCountDTO() == 2);
	assert(raportDTO[1].getNumeDTO() == "napolitane");
	assert(raportDTO[1].getCountDTO() == 1);
	assert(raportDTO[2].getCountDTO() == 2);

	srv.removeProduct(1);
	srv.removeProduct(2);
	srv.removeProduct(3);
	assert(srv.ListSize() == 0);
}

