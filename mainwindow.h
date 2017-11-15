#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

#include "uniface.h"

namespace Ui {
	class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT
	public:
		explicit MainWindow(QWidget* parent = 0);
		~MainWindow();

		void createModels();

	private:
		Ui::MainWindow* ui;
		QList<UniFace*> uniFaces;
		FileWorker* fileWorker = nullptr;

	private slots:
		void tabChanged(int index);
		void tabClosed(int index);

	protected:
		virtual void resizeEvent(QResizeEvent* event);
};

#endif // MAINWINDOW_H
