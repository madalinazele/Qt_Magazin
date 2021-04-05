#include "Qt_Store.h"
#include <QtWidgets/QApplication>
#include "TestRepo.h"
#include "TestService.h"
#include "TestValid.h"
#include "TestDomain.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	testAllRepos();
	testAllService();
	testAllDomain();
	testAllValid();

	RepoAbstract* repo = new RepoFile("produse.txt");
	RepoCos repoCos(repo);
	Validator val;
	Service srv(repo, val, repoCos);
	StoreGUI gui(srv);
	gui.show();
	return a.exec();
}
