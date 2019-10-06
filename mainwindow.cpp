#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <random>
#include <iostream>

#include "src/BSTree.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButtonBSTGenerate_clicked()
{
	auto size = ui->spinBoxNodesNum->value ();
	using namespace std;
	vector<int> v;
	v.resize (size);
	for (auto i = 0; i < size; ++i) {
		v[i] = i;
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(v.begin (), v.end (), g);
	BSTree<int>(v.begin (), v.end ());
}
