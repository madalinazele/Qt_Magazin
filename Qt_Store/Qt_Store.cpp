#include "Qt_Store.h"
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListWidget>
#include <QStateMachine>

void StoreGUI::initGUICmps() {

	resize(900, 450);

	this->setWindowTitle("Products Manager");

	layHorizontal = new QHBoxLayout;
	this->setLayout(layHorizontal);


	QPixmap bkgnd("bkg.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	widLeft = new QWidget;
	widRight = new QWidget;
	rightBtns = new QWidget();
	layHorizontal->addWidget(widLeft);
	layHorizontal->addWidget(widRight);
	layHorizontal->addWidget(rightBtns);

	layLeft = new QVBoxLayout(widLeft);
	btnAdd = new QPushButton("Adauga");
	btnUpdate = new QPushButton("Update");
	btnDelete = new QPushButton("Delete");
	btnFind = new QPushButton("Find");
	btnFilter = new QPushButton("Filter");
	btnSort = new QPushButton("Sort");
	btnRaport = new QPushButton("Raport");
	btnUndo = new QPushButton("Undo");
	btnExit = new QPushButton("Exit");

	layLeft->addWidget(btnAdd);
	layLeft->addWidget(btnUpdate);
	layLeft->addWidget(btnDelete);
	layLeft->addWidget(btnFind);
	layLeft->addWidget(btnFilter);
	layLeft->addWidget(btnSort);
	layLeft->addWidget(btnRaport);
	layLeft->addWidget(btnUndo);
	layLeft->addWidget(btnExit);

	btnCosReadOnly = new QPushButton("CosROGUI");
	btnCos = new QPushButton("CosGUI");

	btnAdaugaCos = new QPushButton("AdaugaCos");
	btnGolesteCos = new QPushButton("GolesteCos");
	btnPopuleazaCos = new QPushButton("PopuleazaCos");

	layRight = new QVBoxLayout(widRight);
	layButtons = new QVBoxLayout(rightBtns);
	topRight = new QWidget;
	layRight->addWidget(topRight);
	allLayout = new QFormLayout(topRight);
	productList = new QListWidget();
	allLayout->addWidget(productList);

	widCos = new QWidget;
	layRight->addWidget(widCos);
	layCos = new QGridLayout(widCos);
	layCos->addWidget(btnCosReadOnly, 0, 0, 1, 3);
	layCos->addWidget(btnCos, 0, 3, 1, 3);
	layCos->addWidget(btnAdaugaCos, 1, 0, 1, 2);
	layCos->addWidget(btnGolesteCos, 1, 2, 1, 2);
	layCos->addWidget(btnPopuleazaCos, 1, 4, 1, 2);

	lblPretTotal = new QLabel();
	downLyrExists = false;
}

void StoreGUI::reloadList() {
	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	productList->clear();
	std::vector<Product> allP = srv.getAllProducts();
	for (auto& p : allP) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));

	}
	int total = srv.pretAcumulat();
	delete lblPretTotal;
	lblPretTotal = new QLabel("Pret total: " + QString::number(total));
	allLayout->addWidget(lblPretTotal);
	lblPretTotal->setStyleSheet(" font: bold 18px; ");

	allLayout->setVerticalSpacing(0);
	allLayout->setSpacing(5);
	allLayout->setContentsMargins(20, 10, 20, 10);

}

void StoreGUI::btnAddClicked() {

	newwindow = new QDialog(topRight);
	QFormLayout* layAdd = new QFormLayout(newwindow);

	lblId = new QLabel("Id:");
	lblNume = new QLabel("Nume:");
	lblProducator = new QLabel("Producator:");
	lblTip = new QLabel("Tip:");
	lblPret = new QLabel("Pret:");

	txtId = new QLineEdit();
	txtNume = new QLineEdit();
	txtProducator = new QLineEdit();
	txtTip = new QLineEdit();
	txtPret = new QLineEdit();

	QPushButton* btnAdd2 = new QPushButton("Add");

	layAdd->addWidget(lblId);
	layAdd->addWidget(txtId);

	layAdd->addWidget(lblNume);
	layAdd->addWidget(txtNume);

	layAdd->addWidget(lblProducator);
	layAdd->addWidget(txtProducator);

	layAdd->addWidget(lblTip);
	layAdd->addWidget(txtTip);

	layAdd->addWidget(lblPret);
	layAdd->addWidget(txtPret);

	layAdd->addWidget(btnAdd2);

	layAdd->setVerticalSpacing(0);
	layAdd->setSpacing(5);
	layAdd->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layAdd);
	newwindow->show();

	connect(btnAdd2, SIGNAL(clicked()), this, SLOT(addCall()));
}

void StoreGUI::btnUpdateClicked() {
	QListWidgetItem* it = productList->currentItem();
	if (it == 0)
	{
		QMessageBox::information(this, "info", "Nu a fost selectat nici un produs!");
		return;
	}
	selectedId = it->data(Qt::UserRole).toInt();

	newwindow = new QDialog(topRight);
	QFormLayout* layUpdate = new QFormLayout(newwindow);

	lblNume = new QLabel("Nume:");
	lblProducator = new QLabel("Producator:");
	lblTip = new QLabel("Tip:");
	lblPret = new QLabel("Pret:");

	txtNume = new QLineEdit();
	txtProducator = new QLineEdit();
	txtTip = new QLineEdit();
	txtPret = new QLineEdit();

	QPushButton* btnUpdate2 = new QPushButton("Update Product");


	layUpdate->addWidget(lblNume);
	layUpdate->addWidget(txtNume);

	layUpdate->addWidget(lblProducator);
	layUpdate->addWidget(txtProducator);

	layUpdate->addWidget(lblTip);
	layUpdate->addWidget(txtTip);

	layUpdate->addWidget(lblPret);
	layUpdate->addWidget(txtPret);

	layUpdate->addWidget(btnUpdate2);

	layUpdate->setVerticalSpacing(0);
	layUpdate->setSpacing(5);
	layUpdate->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layUpdate);
	newwindow->show();

	connect(btnUpdate2, SIGNAL(clicked()), this, SLOT(updateCall()));
}

void StoreGUI::btnDeleteClicked() {

	newwindow = new QDialog(topRight);
	QFormLayout* layDelete = new QFormLayout(newwindow);

	lblId = new QLabel("Id:");
	txtId = new QLineEdit();

	QPushButton* btnDelete2 = new QPushButton("Delete Product");

	layDelete->addWidget(lblId);
	layDelete->addWidget(txtId);

	layDelete->addWidget(btnDelete2);

	layDelete->setVerticalSpacing(0);
	layDelete->setSpacing(5);
	layDelete->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layDelete);
	newwindow->show();

	connect(btnDelete2, SIGNAL(clicked()), this, SLOT(deleteCall()));
}

void StoreGUI::btnFindClicked() {
	newwindow = new QDialog(topRight);
	QFormLayout* layFind = new QFormLayout(newwindow);

	lblId = new QLabel("Id:");
	txtId = new QLineEdit();

	QPushButton* btnFind2 = new QPushButton("Find Product");

	layFind->addWidget(lblId);
	layFind->addWidget(txtId);

	layFind->addWidget(btnFind2);

	layFind->setVerticalSpacing(0);
	layFind->setSpacing(5);
	layFind->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layFind);
	newwindow->show();

	connect(btnFind2, SIGNAL(clicked()), this, SLOT(findCall()));
}

void StoreGUI::btnFilterClicked() {
	if (downLyrExists) {
		delete downRight;
	}
	downRight = new QWidget;
	downLyrExists = true;
	layRight->addWidget(downRight);

	QVBoxLayout* options = new QVBoxLayout(downRight);

	QRadioButton* btnfilterName = new QRadioButton("Filter by name", this);
	QRadioButton* btnfilterProducator = new QRadioButton("Filter by producator", this);
	QRadioButton* btnfilterPrice = new QRadioButton("Filter by price", this);
	btnfilterName->setStyleSheet("font: bold 18px; ");
	btnfilterProducator->setStyleSheet("font: bold 18px; ");
	btnfilterPrice->setStyleSheet("font: bold 18px; ");

	options->addWidget(btnfilterName);
	options->addWidget(btnfilterProducator);
	options->addWidget(btnfilterPrice);

	options->setSpacing(5);
	options->setContentsMargins(30, 10, 20, 10);

	widRight->setLayout(options);
	widRight->show();

	connect(btnfilterName, SIGNAL(clicked()), this, SLOT(btnfilterNameClicked()));
	connect(btnfilterProducator, SIGNAL(clicked()), this, SLOT(btnfilterProdClicked()));
	connect(btnfilterPrice, SIGNAL(clicked()), this, SLOT(btnfilterPriceClicked()));
}

void StoreGUI::btnSortClicked() {
	if (downLyrExists) {
		delete downRight;
	}
	downRight = new QWidget;
	downLyrExists = true;
	layRight->addWidget(downRight);

	QVBoxLayout* options = new QVBoxLayout(downRight);

	QPushButton* btnsortName = new QPushButton("Sort by name");
	QPushButton* btnsortNType = new QPushButton("Sort by name+type");
	QPushButton* btnsortPrice = new QPushButton("Sort by price");

	options->addWidget(btnsortName);
	options->addWidget(btnsortPrice);
	options->addWidget(btnsortNType);

	widRight->setLayout(options);
	widRight->show();

	connect(btnsortName, SIGNAL(clicked()), this, SLOT(sortNameCall()));
	connect(btnsortNType, SIGNAL(clicked()), this, SLOT(sortNameTypeCall()));
	connect(btnsortPrice, SIGNAL(clicked()), this, SLOT(sortPriceCall()));
}

void StoreGUI::btnfilterNameClicked() {
	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	newwindow = new QDialog(topRight);
	QFormLayout* layFilterN = new QFormLayout(newwindow);

	lblNume = new QLabel("String:");
	txtNume = new QLineEdit();

	QPushButton* btnFilterN2 = new QPushButton("Filter");

	layFilterN->addWidget(lblNume);
	layFilterN->addWidget(txtNume);

	layFilterN->addWidget(btnFilterN2);

	layFilterN->setVerticalSpacing(0);
	layFilterN->setSpacing(5);
	layFilterN->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layFilterN);
	newwindow->show();

	connect(btnFilterN2, SIGNAL(clicked()), this, SLOT(filterNameCall()));
}

void StoreGUI::btnfilterProdClicked() {
	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	newwindow = new QDialog(topRight);
	QFormLayout* layFilterP = new QFormLayout(newwindow);

	lblProducator = new QLabel("String:");
	txtProducator = new QLineEdit();

	QPushButton* btnFilterP2 = new QPushButton("Filter");

	layFilterP->addWidget(lblProducator);
	layFilterP->addWidget(txtProducator);

	layFilterP->addWidget(btnFilterP2);

	layFilterP->setVerticalSpacing(0);
	layFilterP->setSpacing(5);
	layFilterP->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layFilterP);
	newwindow->show();

	connect(btnFilterP2, SIGNAL(clicked()), this, SLOT(filterProdCall()));
}

void StoreGUI::btnfilterPriceClicked() {
	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	newwindow = new QDialog(topRight);
	QGridLayout* layFilterPr = new QGridLayout(newwindow);

	lblPret = new QLabel("Pret minim:");
	lblId = new QLabel("Pret maxim:");

	txtPret = new QLineEdit();
	txtId = new QLineEdit();

	QPushButton* btnFilterPr2 = new QPushButton("Filter");

	layFilterPr->addWidget(lblPret, 0, 0, 1, 1);
	layFilterPr->addWidget(txtPret, 0, 1, 1, 1);

	layFilterPr->addWidget(lblId, 1, 0, 1, 1);
	layFilterPr->addWidget(txtId, 1, 1, 1, 1);

	layFilterPr->addWidget(btnFilterPr2, 2, 0, 1, 2);

	layFilterPr->setVerticalSpacing(0);
	layFilterPr->setSpacing(5);
	layFilterPr->setContentsMargins(20, 50, 20, 50);

	newwindow->setLayout(layFilterPr);
	newwindow->show();

	connect(btnFilterPr2, SIGNAL(clicked()), this, SLOT(filterPriceCall()));
}

void StoreGUI::filterNameCall() {
	std::vector<Product> filterList;
	try {
		srv.filtrareNume(filterList, txtNume->text().toStdString());
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide");
	}
	delete newwindow;
	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;
	QFormLayout* filterLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	filterLayout->addWidget(productList);


	for (auto& p : filterList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	filterLayout->setVerticalSpacing(0);
	filterLayout->setSpacing(5);
	filterLayout->setContentsMargins(20, 10, 20, 10);
}

void StoreGUI::filterProdCall() {
	std::vector<Product> filterList;
	try {
		srv.filtrareProducator(filterList, txtProducator->text().toStdString());
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide");
	}
	delete newwindow;
	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;

	QFormLayout* filterLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	filterLayout->addWidget(productList);

	for (auto& p : filterList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	filterLayout->setVerticalSpacing(0);
	filterLayout->setSpacing(5);
	filterLayout->setContentsMargins(20, 10, 20, 10);
}


void StoreGUI::filterPriceCall() {
	std::vector<Product> filterList;
	try {
		srv.filtrarePret(filterList, txtPret->text().toInt(), txtId->text().toInt());
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide");
	}
	delete newwindow;

	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;

	QFormLayout* filterLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	filterLayout->addWidget(productList);

	for (auto& p : filterList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	filterLayout->setVerticalSpacing(0);
	filterLayout->setSpacing(5);
	filterLayout->setContentsMargins(20, 10, 20, 10);
}

void StoreGUI::addCall() {
	try {
		srv.addProduct(txtId->text().toInt(), txtNume->text().toStdString(), txtProducator->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toInt());
		QMessageBox::information(this, "Info", "Produs adaugat!");
	}
	catch (RepoException&) {
		QMessageBox::information(this, "Info", "Produsul exista deja in magazin!");
	}
	catch (ValidateException&) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide!");
	}
	delete newwindow;
	reloadList();
	generateButtons(srv.getAllProducts());
}

void StoreGUI::updateCall() {
	try {
		srv.updateProduct(selectedId, txtNume->text().toStdString(), txtProducator->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toInt());
		QMessageBox::information(this, "Info", "Produs modificat!");
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Nu exista produsul in magazin!");
	}
	catch (ValidateException& ex) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide!");
	}
	delete newwindow;
	reloadList();
	generateButtons(srv.getAllProducts());
}

void StoreGUI::deleteCall() {
	QListWidgetItem* it = productList->currentItem();
	if (it != 0) {
		selectedId = it->data(Qt::UserRole).toInt();
		try {
			srv.removeProduct(selectedId);
			QMessageBox::information(this, "Info", "Produs sters!");
		}
		catch (RepoException& msg) {
			QMessageBox::information(this, "Info", "Datele introduse nu au fost valide");
		}
	}
	else {
		QMessageBox::information(this, "Info", "Niciun produs nu a fost selectat");
	}
	reloadList();
	generateButtons(srv.getAllProducts());
}

void StoreGUI::findCall() {
	try {
		Product p = srv.getProductById(txtId->text().toInt());
		QMessageBox::information(this, "Info", "Produs gasit!");

		delete newwindow;
		if (downLyrExists) {
			delete downRight;
		}

		downRight = new QWidget;
		layRight->addWidget(downRight);
		downLyrExists = true;

		QVBoxLayout* options = new QVBoxLayout(downRight);
		downRight->setContentsMargins(20, 50, 20, 50);

		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QLabel* lblFound = new QLabel("Produsul cautat: ");
		lblFound->setStyleSheet("font: bold 18px; ");
		QLabel* lblFoundProduct = new QLabel(text);
		lblFoundProduct->setStyleSheet(" font: bold 18px; ");
		options->addWidget(lblFound);
		options->addWidget(lblFoundProduct);

	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Nu exista produs cu id ul dat!");

		delete newwindow;
		reloadList();
	}

}

void StoreGUI::sortNameCall() {
	std::vector<Product> sortedList = srv.getAllProducts();
	try {
		srv.sortareNume(sortedList);
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide!");
	}
	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;

	QFormLayout* sortLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	sortLayout->addWidget(productList);


	for (auto& p : sortedList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	sortLayout->setVerticalSpacing(0);
	sortLayout->setSpacing(5);
	sortLayout->setContentsMargins(20, 10, 20, 10);

	generateButtons(sortedList);
}

void StoreGUI::sortNameTypeCall() {
	std::vector<Product> sortedList = srv.getAllProducts();
	try {
		srv.sortareNumeTip(sortedList);
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide");
	}

	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;

	QFormLayout* sortLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	sortLayout->addWidget(productList);

	for (auto& p : sortedList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	sortLayout->setVerticalSpacing(0);
	sortLayout->setSpacing(5);
	sortLayout->setContentsMargins(20, 10, 20, 10);
	generateButtons(sortedList);
}


void StoreGUI::sortPriceCall() {
	std::vector<Product> sortedList = srv.getAllProducts();
	try {
		srv.sortarePret(sortedList);
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Datele introduse nu au fost valide");
	}

	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;

	QFormLayout* sortLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	sortLayout->addWidget(productList);

	for (auto& p : sortedList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	sortLayout->setVerticalSpacing(0);
	sortLayout->setSpacing(5);
	sortLayout->setContentsMargins(20, 10, 20, 10);

	generateButtons(sortedList);
}

void StoreGUI::raportClicked() {
	std::vector<EntityCountDTO> raportList = srv.raportTip();

	if (downLyrExists) {
		delete downRight;
		downLyrExists = false;
	}
	downRight = new QWidget;
	layRight->addWidget(downRight);
	downLyrExists = true;

	QFormLayout* raportLayout = new QFormLayout(downRight);
	QListWidget* productList = new QListWidget();

	raportLayout->addWidget(productList);

	for (auto& p : raportList) {
		QString text = QString("Nume: ");
		text.append(QString::fromStdString(p.getNumeDTO()));
		text.append("---Type: ");
		text.append(QString::fromStdString(p.getTipDTO()));
		text.append("---Type Count : ");
		text.append(QString::number(p.getCountDTO()));

		QListWidgetItem* item = new QListWidgetItem(text, productList);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getCountDTO()));
	}

	raportLayout->setVerticalSpacing(0);
	raportLayout->setSpacing(5);
	raportLayout->setContentsMargins(20, 10, 20, 10);
}
void StoreGUI::undoClicked() {
	try {
		srv.undo();
		QMessageBox::information(this, "Info", "Operatie efectuata!");
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Nu mai exista operatii ce pot fi refacute!");
	}
	reloadList();
	generateButtons(srv.getAllProducts());
}

void StoreGUI::generateButtons(vector<Product> allP)
{
	while (auto button = layButtons->takeAt(0))//fac clear la layout
	{
		delete button->widget();
		delete button;
	}
	for (const auto& produs : allP)
	{
		auto generatedButton = new QPushButton{ QString::fromStdString(produs.getNume()) };
		layButtons->addWidget(generatedButton);
		QObject::connect(generatedButton, &QPushButton::clicked, [this, generatedButton, produs]()
			{
				srv.removeProduct(produs.getId());
				reloadList();
				delete generatedButton;
			});
	}
}

void StoreGUI::btnAddCosClicked() {

	newwindow = new QDialog(topRight);
	QFormLayout* layAdd = new QFormLayout(newwindow);

	lblNume = new QLabel("Nume:");
	txtNume = new QLineEdit();

	QPushButton* btnAdd2 = new QPushButton("Add");

	layAdd->addWidget(lblNume);
	layAdd->addWidget(txtNume);

	layAdd->addWidget(btnAdd2);

	newwindow->setLayout(layAdd);
	newwindow->show();

	connect(btnAdd2, &QPushButton::clicked, [&]() {
		try {
			srv.adaugaCos(txtNume->text().toStdString());
			QMessageBox::information(this, "Info", "Produsul a fost adaugat in cos!");
		}
		catch (RepoException& msg) {
			QMessageBox::information(this, "Info", "Produsul nu exista in magazin!");
		}
		delete newwindow;
		});

}

void StoreGUI::btnPopulateCosClicked() {

	newwindow = new QDialog(topRight);
	QFormLayout* layPopulate = new QFormLayout(newwindow);

	lblPret = new QLabel("Numar produse:");
	txtPret = new QLineEdit();

	QPushButton* btnPopulate2 = new QPushButton("Populate");

	layPopulate->addWidget(lblPret);
	layPopulate->addWidget(txtPret);

	layPopulate->addWidget(btnPopulate2);

	newwindow->setLayout(layPopulate);
	newwindow->show();

	connect(btnPopulate2, &QPushButton::clicked, [&]() {
		srv.populateCosP(txtPret->text().toInt());
		QMessageBox::information(this, "Info", "Cosul a fost populat!");
		delete newwindow;
		});

}

void StoreGUI::connectSignalsSlots() {

	connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
	connect(btnUpdate, SIGNAL(clicked()), this, SLOT(btnUpdateClicked()));
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteCall()));
	connect(btnFind, SIGNAL(clicked()), this, SLOT(btnFindClicked()));
	connect(btnFilter, SIGNAL(clicked()), this, SLOT(btnFilterClicked()));
	connect(btnSort, SIGNAL(clicked()), this, SLOT(btnSortClicked()));
	connect(btnRaport, SIGNAL(clicked()), this, SLOT(raportClicked()));
	connect(btnUndo, SIGNAL(clicked()), this, SLOT(undoClicked()));
	connect(btnExit, SIGNAL(clicked()), qApp, SLOT(quit()));

	connect(btnAdaugaCos, SIGNAL(clicked()), this, SLOT(btnAddCosClicked()));
	connect(btnPopuleazaCos, SIGNAL(clicked()), this, SLOT(btnPopulateCosClicked()));
	connect(btnCos, &QPushButton::clicked, [&]() {
		auto cos = new CosGUI{ srv };
		cos->show();
		});

	connect(btnCosReadOnly, &QPushButton::clicked, [&]() {
		auto cos = new CosReadOnlyGUI{ srv };
		cos->show();
		});

	connect(btnGolesteCos, &QPushButton::clicked, [&]() {
		srv.emptyCosP();
		QMessageBox::information(this, "Info", "Cosul a fost golit!");
		});
}