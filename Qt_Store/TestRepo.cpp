#include <cassert>
#include"TestRepo.h"
#include <exception>

void testAllRepos() {
	RepoAbstract* repo = new Repository;
	testAllRepo(repo);
	delete repo;

	try {
		RepoAbstract* repoFile = new RepoFile("somefile.txt");
	}
	catch (RepoException&) {
		assert(true);
	}
	ofstream g("test.txt", ofstream::out | ofstream::trunc);
	g.close();
	RepoAbstract* repoFile = new RepoFile("test.txt");
	testAllRepo(repoFile);
	delete repoFile;

	try {
		RepoAbstract* repoNou = new RepoNou(0.0);
	}
	catch (RepoException&) {
		assert(true);
	}
	RepoAbstract* repoNou = new RepoNou(1.0);
	testAllRepo(repoNou);
	delete repoNou;
}

void testAllRepo(RepoAbstract* repo) {
	testAdd(repo);
	testUpdate(repo);
	testRemove(repo);
	testAdaugaCos(repo);
	testStergeCos(repo);
	testModificaCos(repo);
	testSavetoFile(repo);
}

void testAdd(RepoAbstract* repo) {

	Product p1(1, "ciocolata", "milka", "alba", 4);
	Product p2(2, "napolitane", "alka", "vanilie", 3);

	repo->add(p1);
	repo->add(p2);

	try {
		Product p3(1, "gem", "tara", "afine", 10);
		repo->add(p3);
	}
	catch (RepoException&) {
		assert(true);
	}

	int size;
	size = repo->size();
	assert(size == 2);
	assert(repo->findById(2).getPret() == 3);
	assert(repo->findById(1).getNume() == "ciocolata");

	repo->remove(2);
	repo->remove(1);
	assert(repo->size() == 0);
}

void testUpdate(RepoAbstract* repo) {
	Product p1(1, "ciocolata", "milka", "alba", 4);
	Product p2(2, "napolitane", "alka", "vanilie", 3);

	repo->add(p1);
	repo->add(p2);

	Product p3(1, "cioco", "milka", "caramel", 5);
	repo->update(p3);

	try {
		Product p4(6, "gem", "tara", "afine", 10);
		repo->update(p4);
	}
	catch (RepoException&) {
		assert(true);
	}

	int size;
	size = repo->size();
	assert(size == 2);
	assert(repo->findById(2).getPret() == 3);
	assert(repo->findById(1).getNume() == "cioco");

	repo->remove(1);
	repo->remove(2);
	assert(repo->size() == 0);
}

void testRemove(RepoAbstract* repo) {
	Product p1(1, "ciocolata", "milka", "alba", 4);
	Product p2(2, "napolitane", "alka", "vanilie", 3);

	repo->add(p1);
	repo->add(p2);

	repo->remove(2);

	try {
		repo->remove(9);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		repo->findById(2);
	}
	catch (RepoException&) {
		assert(true);
	}
	assert(repo->size() == 1);
	assert(repo->findById(1).getPret() == 4);
	assert(repo->findById(1).getNume() == "ciocolata");

	repo->remove(1);
	assert(repo->size() == 0);
}

void testAdaugaCos(RepoAbstract* repo) {
	RepoCos repoCos(repo);
	Product p1(1, "ciocolata", "milka", "alba", 4);
	Product p2(2, "napolitane", "alka", "vanilie", 3);

	repo->add(p1);
	repo->add(p2);

	repoCos.addCos("ciocolata");
	assert(repoCos.pretTotal() == 4);
	repoCos.addCos("napolitane");
	assert(repoCos.pretTotal() == 7);

	try {
		repoCos.addCos("gem");
	}
	catch (RepoException&) {
		assert(true);
	}

	assert(repoCos.size() == 2);
	vector<Product> allP = repoCos.getAllCos();
	assert(allP.at(0).getTip() == "alba");
	assert(allP.at(1).getProducator() == "alka");

	repoCos.emptyCos();
	assert(repoCos.size() == 0);

	repoCos.populateCos(10);
	assert(repoCos.size() == 10);

	repo->remove(1);
	repo->remove(2);
	assert(repo->size() == 0);
}

void testStergeCos(RepoAbstract* repo) {
	RepoCos repoCos(repo);

	Product p1(1, "ciocolata", "milka", "alba", 4);
	Product p2(2, "napolitane", "alka", "vanilie", 3);

	repo->add(p1);
	repo->add(p2);

	repoCos.addCos("ciocolata");
	assert(repoCos.pretTotal() == 4);
	repoCos.addCos("napolitane");
	repoCos.addCos("ciocolata");
	assert(repoCos.pretTotal() == 11);
	assert(repoCos.size() == 3);

	repoCos.stergeElemente(1);
	assert(repoCos.pretTotal() == 3);
	assert(repoCos.size() == 1);

	repoCos.stergeElemente(6);
	assert(repoCos.pretTotal() == 3);
	assert(repoCos.size() == 1);

	vector<Product> allP = repoCos.getAllCos();
	assert(allP.at(0).getNume() == "napolitane");

	repo->remove(1);
	repo->remove(2);
	assert(repo->size() == 0);
}

void testModificaCos(RepoAbstract* repo) {
	RepoCos repoCos(repo);

	Product p1(1, "cioco", "milka", "alba", 4);
	Product p2(2, "napolitane", "alka", "vanilie", 3);

	repo->add(p1);
	repo->add(p2);

	repoCos.addCos("cioco");
	repoCos.addCos("napolitane");
	repoCos.addCos("cioco");
	assert(repoCos.pretTotal() == 11);
	assert(repoCos.size() == 3);

	Product p3(1, "ciocolata", "milka", "alune", 5);
	repoCos.modificaElemente(p3);

	assert(repoCos.size() == 3);
	assert(repoCos.pretTotal() == 13);
	repoCos.modificaElemente(Product(4, "gem", "buni", "afine", 14));
	assert(repoCos.pretTotal() == 13);
	assert(repoCos.size() == 3);

	vector<Product> allP = repoCos.getAllCos();
	assert(allP.at(0).getNume() == "ciocolata");
	assert(allP.at(1).getProducator() == "alka");

	repoCos.emptyCos();
	assert(repoCos.pretTotal() == 0);

	repo->remove(1);
	repo->remove(2);
	assert(repo->size() == 0);
}

void testSavetoFile(RepoAbstract* repo) {
	RepoCos repoCos(repo);

	repo->add(Product(1, "ciocolata", "milka", "alba", 8));
	repo->add(Product(2, "napolitane", "alka", "rom", 5));

	repoCos.populateCos(10);
	assert(repoCos.size() == 10);

	repoCos.saveCos("testCos.csv");
	assert(repoCos.size() == 10);

	repoCos.emptyCos();
	repoCos.saveCos("testCos.csv");
	assert(repoCos.pretTotal() == 0);

	repo->remove(1);
	repo->remove(2);
	assert(repo->size() == 0);
}
