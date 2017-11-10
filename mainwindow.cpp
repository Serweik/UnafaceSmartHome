#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	GlobalVarFromResourcesLoader::load();
	globalVar.mainWindowMinSize = this->minimumSize();
	fileWorker = new FileWorker(this);
	QString CurrentDir = QApplication::applicationDirPath() + "/";
	InterfaceConfigs interfaceConfigs = fileWorker->readInterfaceConfigs(CurrentDir + globalVar.strings.value("configsFile") + ".xml");
	globalVar.mainWindowSize = interfaceConfigs.windowSize;

	QDir interfacesDirectories(CurrentDir);
	QString dirPostfix = globalVar.strings.value("configsDirPostfix");
	QStringList directories = interfacesDirectories.entryList(QStringList() << "*" + dirPostfix, QDir::Dirs | QDir::NoDotAndDotDot);
	foreach(QString interfaceDir, directories) {
		UniFace* uniFace = new UniFace(this);
		connect(fileWorker, SIGNAL(modelBuilded(QList<QGraphicsScene*>, ModelConfigs)), uniFace, SLOT(setNewModel(QList<QGraphicsScene*>, ModelConfigs)));
		uniFaces.append(uniFace);
		fileWorker->buildModel(CurrentDir + interfaceDir + "/", (size_t*)uniFace);
		ui->tabWidget->addTab(uniFace->graphicsView, interfaceDir.remove(interfaceDir.length() - dirPostfix.length(), dirPostfix.length()));
	}
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	globalVar.mainWindowSize = event->size();
	setWindowTitle("Universal interface (Size: " + QString::number(globalVar.mainWindowSize.width()) + "x" + QString::number(globalVar.mainWindowSize.height()) + ")");
	if(ui->tabWidget->currentIndex() >= 0) {
		uniFaces.at(ui->tabWidget->currentIndex())->resize();
	}
	QMainWindow::resizeEvent(event);
}
