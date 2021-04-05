#pragma once

#include <QtWidgets/QMainWindow>
#include "Service.h"
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QLineEdit>
#include "Observer.h"
#include <qpainter.h>
#include <qimage.h>
#include <qdatetime.h>
#include <qdebug.h>

class CosGUI : public QWidget, public Observer {
	Q_OBJECT
private:
	Service& srv;
	void initGUICmps();
	void connectSignalsSlots();

public:
	CosGUI(Service& srv) : srv{ srv } {
		initGUICmps();
		connectSignalsSlots();
		reloadList();
	}
	~CosGUI() {
		srv.removeObserver(this);
	}
	void update() override {
		reloadList();
	}

	void reloadList();
	QHBoxLayout* layHorizontal;

	QWidget* widLeft;
	QVBoxLayout* layLeft;
	QLabel* lblMenu;
	QListWidget* menuList;

	QPushButton* btnAdd;
	QPushButton* btnPopulate;
	QPushButton* btnEmpty;
	QPushButton* btnSave;
	QPushButton* btnTotal;

	QWidget* widRight;
	QVBoxLayout* layRight;

	QLabel* lblId;
	QLabel* lblNume;
	QLabel* lblProducator;
	QLabel* lblTip;
	QLabel* lblPret;
	QLabel* lblpretTotal;
	QLabel* lblnrProd;

	QLineEdit* txtId;
	QLineEdit* txtNume;
	QLineEdit* txtProducator;
	QLineEdit* txtTip;
	QLineEdit* txtPret;

	QWidget* topRight;
	QFormLayout* listLayout;
	QListWidget* allP;
	QListWidgetItem* item;
	QDialog* dial;

public slots:

	void btnAddClicked();
	void btnPopulateClicked();
	void btnSaveClicked();
	void btnEmptyClicked();

	void addCall();
	void populateCall();
	void saveCall();

};


class CosReadOnlyGUI : public QWidget, public Observer {
	Q_OBJECT
private:
	Service& srv;
	std::vector<QColor> culori;
	void initGUICmps();

public:
	void reloadList() {
		repaint();
	}

	CosReadOnlyGUI(Service& srv) : srv{ srv } {
		initGUICmps();
		reloadList();
	}
	~CosReadOnlyGUI() {
		srv.removeObserver(this);
	}
	void update() override {
		reloadList();
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };

		for (auto& produs : srv.getAllProductsCos())
		{
			QPen pen;
			int c = rand() % 10;
			pen.setColor(culori[c]);
			pen.setWidth(5);
			pen.setStyle(Qt::SolidLine);
			p.setPen(pen);

			QRect forma(qrand() % 350, qrand() % 150, qrand() % 200, qrand() % 150);
			forma.normalized();
			p.drawRect(forma);
		}
	}

	QHBoxLayout* layHorizontal;

	QWidget* widCentral;
	QLabel* lblnumarProduse;


};