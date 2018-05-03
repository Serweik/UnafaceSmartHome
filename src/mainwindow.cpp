#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	GlobalVarFromResourcesLoader::load();
	globalVar.mainWindowMinSize = this->minimumSize();
	fileWorker = new FileWorker(this);
	QString currentDir = QApplication::applicationDirPath() + "/";
	InterfaceConfigs interfaceConfigs = fileWorker->readInterfaceConfigs(currentDir + globalVar.strings.value("mainConfigsFile") + ".xml");
	globalVar.mainWindowSize = interfaceConfigs.windowSize;

	QDir interfacesDirectories(currentDir);
	QString dirPostfix = globalVar.strings.value("configsDirPostfix");
	QStringList directories = interfacesDirectories.entryList(QStringList() << "*" + dirPostfix, QDir::Dirs | QDir::NoDotAndDotDot);
	foreach(QString interfaceDir, directories) {
		UniFace* uniFace = new UniFace(this);
		uniFace->setCurrentPath(currentDir);
		uniFace->setInterfaceDirName(interfaceDir);
		uniFaces.append(uniFace);
		ui->tabWidget->addTab(uniFace->graphicsView, interfaceDir.remove(interfaceDir.length() - dirPostfix.length(), dirPostfix.length()));
	}
	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
	connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabClosed(int)));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::createModels() {
	foreach(UniFace* uniFace, uniFaces) {
		connect(fileWorker, SIGNAL(modelBuilded(QList<QGraphicsScene*>, ModelConfigs)), uniFace, SLOT(setNewModel(QList<QGraphicsScene*>, ModelConfigs)));
		fileWorker->buildModel(uniFace->getCurrentPath() + uniFace->getInterfaceDirName() + "/", (size_t*)uniFace);
	}
}

void MainWindow::tabChanged(int index) {
	if((index >= 0) && (index < uniFaces.size())) {
		uniFaces.at(index)->resize();
	}
}

void MainWindow::tabClosed(int index) {
	ui->tabWidget->removeTab(index);
	if((ui->tabWidget->currentIndex() >= 0) && (ui->tabWidget->currentIndex() < uniFaces.size())) {
		uniFaces.at(ui->tabWidget->currentIndex())->resize();
	}
	if((index >= 0) && (index < uniFaces.size())) {
		//@TODO сначала сохранить изменения в файлы!
		uniFaces.at(index)->deleteLater();
		uniFaces.removeAt(index);
	}
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	globalVar.mainWindowSize = event->size();
	QMainWindow::resizeEvent(event);
	setWindowTitle("Universal interface (Size: " + QString::number(globalVar.mainWindowSize.width()) + "x" + QString::number(globalVar.mainWindowSize.height()) + ")");
	if((ui->tabWidget->currentIndex() >= 0) && (ui->tabWidget->currentIndex() < uniFaces.size())) {
		uniFaces.at(ui->tabWidget->currentIndex())->resize();
	}
}
