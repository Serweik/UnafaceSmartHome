#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <QMap>
#include <QSize>

#define NAME_TO_STRING(name) (#name)

struct GlobalVariables {
	QSize mainWindowMinSize;
	QSize mainWindowSize;
	QSize graphicsViewSize;	//все представления имеют один размер
	QMap<QString, QString> strings;
};

extern GlobalVariables globalVar;

#endif // GLOBALVARIABLES_H
