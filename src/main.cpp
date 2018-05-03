#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	//костыль для того чтобы graphicsView, установленный в TabWidget получил корректный размер.
	//пока не понятно как сделать правильнее и почему размер становится верным только при втором ресайзе (первый происходит во время w.show())
	QSize tempWindowSize = globalVar.mainWindowSize;	// globalVar.mainWindowSize изменится ппосле выполнения ресайза
	w.resize(globalVar.mainWindowSize - QSize(1,1));
	w.resize(tempWindowSize);
	w.createModels();	//модели создаем только после того как устаканились все размеры

	return a.exec();
}
