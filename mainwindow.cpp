#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <random>
#include <iostream>
#include "node_view.h"

#include "src/BSTree.h"

struct MainWindow::impl {
	using key_type = Key<NodeView*>;

	BSTree<key_type> bstree;

	template <class Gen, class Data=key_type>
	auto randomItems(size_t num, const Gen &generator) -> std::vector<Data>
	{
		using namespace std;
		assert(num > 0);
		vector<Data> out;
		out.resize (num);

		for (size_t i = 0; i < num; ++i) {
			out[i] = generator(i);
		}

		random_device rd;
		mt19937 g(rd());
		shuffle(out.begin (), out.end (), g);
		return out;
	}

	template<class Gen>
	void loadRandomBSTree(size_t num, Gen&& generator) {
		using namespace std;
		auto v = randomItems(num, generator);
		bstree = {v.begin (), v.end ()};
	}
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(std::make_unique<Ui::MainWindow>())
{
	ui->setupUi(this);
	pimpl = std::make_unique<impl>();
}


MainWindow::~MainWindow() = default;

void MainWindow::on_pushButtonBSTGenerate_clicked()
{

	resetScene();

	auto generator = [&](size_t i){
		auto graphView = ui->graphicsViewBSTree;

		NodeView* nodeView = new NodeView(graphView);
		graphView->addItem(nodeView);

		return Key<NodeView*>{i, nodeView};
	};
	int size = ui->spinBoxNodesNum->value();
	assert(size > 0);
	pimpl->loadRandomBSTree(static_cast<size_t>(size), generator);
}

void MainWindow::resetScene()
{
	auto graphView = ui->graphicsViewBSTree;
	graphView->clear();
}
