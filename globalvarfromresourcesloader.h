#ifndef GLOBALVARFROMRESOURCESLOADER_H
#define GLOBALVARFROMRESOURCESLOADER_H

#include <QtXml>
#include <QFile>
#include <QTextStream>

#include "globalvariables.h"

class GlobalVarFromResourcesLoader {
	public:
		static void load() {
			if(globalVar.strings.size() == 0) {
				QFile file(":/values/strings.xml");
				if(file.open(QFile::ReadOnly | QFile::Text)) {
					QDomDocument domDoc;
					if(domDoc.setContent(&file)) {
						QDomElement domElement = domDoc.documentElement();
						if(!domElement.isNull()) {
							for(QDomNode nodeChild = domElement.firstChild(); !nodeChild.isNull(); nodeChild = nodeChild.nextSibling()) {
								QDomElement element = nodeChild.toElement();
								QString key = element.attribute("name");
								QString value = element.text();
								if(!key.isEmpty() && !value.isEmpty()) {
									globalVar.strings.insert(key, value);
								}
							}
						}
					}
					file.close();
				}
			}
		}
	private:
		GlobalVarFromResourcesLoader() = delete;
};

#endif // GLOBALVARFROMRESOURCESLOADER_H
