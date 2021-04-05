#include "CosGUI.h"

void CosGUI::initGUICmps() {
	srv.addObserver(this);
	resize(600, 300);
	this->setWindowTitle("Wish List");
	layHorizontal = new QHBoxLayout;
	this->setLayout(layHorizontal);

	QPixmap bkgnd("bkg.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	widRight = new QWidget;
	widLeft = new QWidget;
	layHorizontal->addWidget(widLeft);
	layHorizontal->addWidget(widRight);

	layLeft = new QVBoxLayout(widLeft);
	btnAdd = new QPushButton("Add");
	btnPopulate = new QPushButton("Populate");
	btnEmpty = new QPushButton("Empty");
	btnSave = new QPushButton("Save to file");

	layLeft->addWidget(btnAdd);
	layLeft->addWidget(btnPopulate);
	layLeft->addWidget(btnEmpty);
	layLeft->addWidget(btnSave);

	layRight = new QVBoxLayout(widRight);
	topRight = new QWidget;
	layRight->addWidget(topRight);
	listLayout = new QFormLayout(topRight);
	allP = new QListWidget();
	listLayout->addWidget(allP);

	lblpretTotal = new QLabel();
	lblnrProd = new QLabel();
}

void CosGUI::reloadList() {
	allP->clear();

	std::vector<Product> productList = srv.getAllProductsCos();
	for (auto& p : productList) {
		QString text = QString::number(p.getId());
		text.append("	");
		text.append(QString::fromStdString(p.getNume()));
		text.append("	");
		text.append(QString::fromStdString(p.getProducator()));
		text.append("	");
		text.append(QString::fromStdString(p.getTip()));
		text.append("	");
		text.append(QString::number(p.getPret()));

		QListWidgetItem* item = new QListWidgetItem(text, allP);
		item->setData(Qt::UserRole, QVariant::fromValue(p.getId()));
	}

	int total = srv.pretTotalCos();
	delete lblpretTotal;
	lblpretTotal = new QLabel("Pret total: " + QString::number(total));
	listLayout->addWidget(lblpretTotal);
	lblpretTotal->setStyleSheet(" font: bold 17px; ");

	int nr = srv.sizeCos();
	delete lblnrProd;
	lblnrProd = new QLabel("Numar produse: " + QString::number(nr));
	listLayout->addWidget(lblnrProd);
	lblnrProd->setStyleSheet(" font: bold 17px; ");

	listLayout->setVerticalSpacing(0);
	listLayout->setSpacing(5);
	listLayout->setContentsMargins(20, 20, 20, 10);
}

void CosGUI::btnAddClicked() {

	dial = new QDialog(topRight);
	QFormLayout* layAdd = new QFormLayout(dial);

	lblNume = new QLabel("Denumire produs:");
	txtNume = new QLineEdit();

	QPushButton* btnAdd2 = new QPushButton("Add");

	layAdd->addWidget(lblNume);
	layAdd->addWidget(txtNume);

	layAdd->addWidget(btnAdd2);

	layAdd->setVerticalSpacing(0);
	layAdd->setSpacing(5);
	layAdd->setContentsMargins(20, 50, 20, 50);

	dial->setLayout(layAdd);
	dial->show();

	connect(btnAdd2, SIGNAL(clicked()), this, SLOT(addCall()));
}

void CosGUI::btnPopulateClicked() {

	dial = new QDialog(topRight);
	QFormLayout* layPopulate = new QFormLayout(dial);

	lblPret = new QLabel("Numar produse:");
	txtPret = new QLineEdit();

	QPushButton* btnPopulate2 = new QPushButton("Populate");

	layPopulate->addWidget(lblPret);
	layPopulate->addWidget(txtPret);

	layPopulate->addWidget(btnPopulate2);

	layPopulate->setVerticalSpacing(0);
	layPopulate->setSpacing(5);
	layPopulate->setContentsMargins(20, 50, 20, 50);

	dial->setLayout(layPopulate);
	dial->show();

	connect(btnPopulate2, SIGNAL(clicked()), this, SLOT(populateCall()));
}

void CosGUI::btnSaveClicked() {

	dial = new QDialog(topRight);
	QFormLayout* laySave = new QFormLayout(dial);

	lblNume = new QLabel("Nume fisier:");
	txtNume = new QLineEdit();

	QPushButton* btnSave2 = new QPushButton("Save");

	laySave->addWidget(lblNume);
	laySave->addWidget(txtNume);

	laySave->addWidget(btnSave2);

	laySave->setVerticalSpacing(0);
	laySave->setSpacing(5);
	laySave->setContentsMargins(20, 50, 20, 50);

	dial->setLayout(laySave);
	dial->show();

	connect(btnSave2, SIGNAL(clicked()), this, SLOT(saveCall()));
}

void CosGUI::btnEmptyClicked() {

	srv.emptyCosP();
	QMessageBox::information(this, "Info", "Cosul a fost golit!");

	reloadList();
}

void CosGUI::addCall() {

	try {
		srv.adaugaCos(txtNume->text().toStdString());
		QMessageBox::information(this, "Info", "Produsul a fost adaugat in cos!");
	}
	catch (RepoException& msg) {
		QMessageBox::information(this, "Info", "Produsul nu exista in magazin!");
	}

	delete dial;
	reloadList();
}

void CosGUI::populateCall() {

	srv.populateCosP(txtPret->text().toInt());
	QMessageBox::information(this, "Info", "Cosul a fost populat!");

	delete dial;
	reloadList();
}

void CosGUI::saveCall() {

	srv.saveToFile(txtNume->text().toStdString());
	QMessageBox::information(this, "Info", "Cosul a fost salvat in fisier!");

	delete dial;
	reloadList();
}

void CosGUI::connectSignalsSlots() {


	connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
	connect(btnPopulate, SIGNAL(clicked()), this, SLOT(btnPopulateClicked()));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));
	connect(btnEmpty, SIGNAL(clicked()), this, SLOT(btnEmptyClicked()));

}

void CosReadOnlyGUI::initGUICmps() {
	srv.addObserver(this);
	resize(600, 300);
	this->setWindowTitle("Wish List");
	layHorizontal = new QHBoxLayout;
	this->setLayout(layHorizontal);

	QPixmap bkgnd("bkg.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	culori.push_back(Qt::red);
	culori.push_back(Qt::blue);
	culori.push_back(Qt::yellow);
	culori.push_back(Qt::black);
	culori.push_back(Qt::green);
	culori.push_back(Qt::cyan);
	culori.push_back(Qt::magenta);
	culori.push_back(Qt::darkBlue);
	culori.push_back(Qt::darkGray);
	culori.push_back(Qt::darkRed);
}