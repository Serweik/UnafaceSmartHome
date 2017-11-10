#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <QMap>
#include <QSize>

struct GlobalVariables {
	QSize mainWindowMinSize;
	QSize mainWindowSize;
	QMap<QString, QString> strings;
};

extern GlobalVariables globalVar;

#endif // GLOBALVARIABLES_H
