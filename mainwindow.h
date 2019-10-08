#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	virtual ~MainWindow();

private slots:

	void on_pushButtonBSTGenerate_clicked();

private:
	void resetScene();
	std::unique_ptr<Ui::MainWindow> ui;
	struct impl;
	std::unique_ptr<impl> pimpl;
};

#endif // MAINWINDOW_H
