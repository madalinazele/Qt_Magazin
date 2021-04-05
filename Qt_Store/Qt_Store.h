#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Store.h"
#include "Service.h"
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include "CosGUI.h"
#include "Observer.h"

class StoreGUI : public QWidget {
	Q_OBJECT
private:

	Service& srv;
	void initGUICmps();
	void connectSignalsSlots();
	void generateButtons(vector<Product> allP);
	void reloadList();

public:
	StoreGUI(Service& srv ) : srv{ srv } {
		initGUICmps();
		connectSignalsSlots();
		reloadList();
		generateButtons(srv.getAllProducts());
	}
	QHBoxLayout* layHorizontal;

	QWidget* widLeft;
	QVBoxLayout* layLeft;
	QLabel* lblMenu;
	QListWidget* menuList;

	QPushButton* btnAdd;
	QPushButton* btnUpdate;
	QPushButton* btnDelete;
	QPushButton* btnFind;
	QPushButton* btnFilter;
	QPushButton* btnSort;
	QPushButton* btnRaport;
	QPushButton* btnUndo;
	QPushButton* btnExit;

	QPushButton* btnCosReadOnly;
	QPushButton* btnCos;
	QPushButton* btnAdaugaCos;
	QPushButton* btnGolesteCos;
	QPushButton* btnPopuleazaCos;
	QGridLayout* layCos;
	QWidget* widRight;
	QVBoxLayout* layRight;

	QLabel* lblId;
	QLabel* lblNume;
	QLabel* lblProducator;
	QLabel* lblTip;
	QLabel* lblPret;
	QLabel* lblPretTotal;
	QLineEdit* txtId;
	QLineEdit* txtNume;
	QLineEdit* txtProducator;
	QLineEdit* txtTip;
	QLineEdit* txtPret;
	int selectedId;
	bool downLyrExists;
	QListWidget* allP;
	QListWidgetItem* item;
	QWidget* downRight;
	QFormLayout* listLayout;
	QDialog* newwindow;
	QWidget* topRight;
	QFormLayout* allLayout;
	QListWidget* productList;
	QWidget* widCos;
	QWidget* rightBtns;
	QVBoxLayout* layButtons;

public slots:
	void btnAddClicked();
	void btnUpdateClicked();
	void btnDeleteClicked();
	void btnFindClicked();
	void btnFilterClicked();
	void btnSortClicked();

	void btnfilterNameClicked();
	void btnfilterProdClicked();
	void btnfilterPriceClicked();

	void addCall();
	void updateCall();
	void deleteCall();
	void findCall();

	void filterNameCall();
	void filterProdCall();
	void filterPriceCall();

	void sortPriceCall();
	void sortNameCall();
	void sortNameTypeCall();

	void raportClicked();
	void undoClicked();

	void btnAddCosClicked();
	void btnPopulateCosClicked();
};

