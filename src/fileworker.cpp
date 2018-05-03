#include "fileworker.h"
#include <QDebug>

FileWorker::FileWorker(QObject* parent):
	QObject(parent) {

}

InterfaceConfigs FileWorker::readInterfaceConfigs(QString pathToConfigs) {
	InterfaceConfigs interfaceConfigs;
	QFile file(pathToConfigs);
	if(file.open(QFile::ReadOnly | QFile::Text)) {
		QDomDocument domDoc;
		if(domDoc.setContent(&file)) {
			QDomElement domElement = domDoc.documentElement();
			if(!domElement.isNull() && (domElement.nodeName() == globalVar.strings.value("mainConfigsFile"))) {
				for(QDomNode nodeChild = domElement.firstChild(); !nodeChild.isNull(); nodeChild = nodeChild.nextSibling()) {
					QDomElement element = nodeChild.toElement();
					QString elementName = element.nodeName();
					if(elementName == globalVar.strings.value("windiwWidth")) {
						int winWidth = element.attribute(globalVar.strings.value("configValue")).toUInt();
						if(winWidth >= globalVar.mainWindowMinSize.width()) {
							interfaceConfigs.windowSize.setWidth(winWidth);
						}
					}else if(elementName == globalVar.strings.value("windiwHeight")) {
						int winHeight = element.attribute(globalVar.strings.value("configValue")).toUInt();
						if(winHeight >= globalVar.mainWindowMinSize.height()) {
							interfaceConfigs.windowSize.setHeight(winHeight);
						}
					}
				}
			}
		}
		file.close();
	}
	return interfaceConfigs;
}

void FileWorker::buildModel(QString pathToConfigs, size_t* targetObjectPtr) {
	if(!pathToConfigs.isEmpty()) {
		QDir directoryForConfigs(pathToConfigs);
		QFileInfoList files = directoryForConfigs.entryInfoList(QStringList() << "*.xml",
								QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);

		ModelConfigs modelConfigs;
		int indexConfigsFile = files.indexOf(QFileInfo(pathToConfigs + "/" + globalVar.strings.value("configsFile") + ".xml"));
		if(indexConfigsFile != -1) {
			modelConfigs = readConfigs(files.takeAt(indexConfigsFile));
		}
		modelConfigs.targetObjectPtr = targetObjectPtr;

		QList<QGraphicsScene*> model;
		foreach(QFileInfo fileInfo, files) {
			QFile file(fileInfo.absoluteFilePath());
			if(file.open(QFile::ReadOnly | QFile::Text)) {
				QDomDocument domDoc;
				if(domDoc.setContent(&file)) {
					QDomElement domElement = domDoc.documentElement();
					if(!domElement.isNull() && (domElement.nodeName() == globalVar.strings.value("subsystemsName"))) {
						QGraphicsScene* scene = createScene(model, modelConfigs, directoryForConfigs, domElement);
						QRectF sceneRect = scene->itemsBoundingRect();
						scene->setSceneRect(0,0, sceneRect.width(), sceneRect.height());
						model.prepend(scene);
					}
				}
				file.close();
			}
		}
		emit modelBuilded(model, modelConfigs);
	}
}

QGraphicsScene* FileWorker::createScene(QList<QGraphicsScene*>& model, const ModelConfigs& modelConfigs, const QDir& directoryForConfigs, const QDomElement& domElement) {
	QGraphicsScene* scene = new QGraphicsScene();
	for(QDomElement elementChild = domElement.firstChildElement(); !elementChild.isNull(); elementChild = elementChild.nextSiblingElement()) {
		ControlTypeBase controlTypeBase;
		QObject* control = createControl(elementChild, controlTypeBase, directoryForConfigs, modelConfigs);
		if(control != nullptr) {
			if(controlTypeBase == LEVELITEM) {
				scene->addItem(qobject_cast<ControlBaseGraphObject*>(control));
				QGraphicsScene* scene = createScene(model, modelConfigs, directoryForConfigs, elementChild);
				LevelControl* levelControl = qobject_cast<LevelControl*>(control);
				levelControl->setLinkToScene(scene);
				QRectF sceneRect = scene->itemsBoundingRect();
				scene->setSceneRect(0,0, sceneRect.width(), sceneRect.height());
				model.prepend(scene);
			}else if(controlTypeBase == Q_GRAPHICS_ITEM) {
				scene->addItem(qobject_cast<ControlBaseGraphObject*>(control));
			}else if(controlTypeBase == Q_WIDGET) {
				scene->addWidget(qobject_cast<QWidget*>(control));
			}
		}
	}
	return scene;
}

QObject* FileWorker::createControl(const QDomElement& element, ControlTypeBase& controlTypeBase, const QDir& directoryForConfigs, const ModelConfigs& modelConfigs) {
	QObject* createdControl = nullptr;
	QString controlType = globalVar.strings.key(element.nodeName());
	if(!controlType.isEmpty()) {
		uint controlTypeId = controlType.section(' ', 0, 0).toUInt();
		if(controlTypeId == 1) {
			//ByteButton
			controlTypeBase = Q_GRAPHICS_ITEM;
			ByteButton* byteButton = nullptr;
			byteButton = UniversalFactory::createObject(byteButton);
			createdControl = byteButton;
			QPixmap pixmap(directoryForConfigs.absolutePath() + "/" + element.attribute(globalVar.strings.value("controlImgOff")));
			if(pixmap.isNull()) {
				pixmap.load(globalVar.strings.value("default noImg"));
			}
			byteButton->setPixmap(pixmap);
			setUnionParamForBaseGraphControl(element, modelConfigs, byteButton);
		}else if(controlTypeId > 1 && controlTypeId < 5) {
			//LevelControl
			controlTypeBase = LEVELITEM;
			LevelControl* levelControl = nullptr;
			levelControl = UniversalFactory::createObject(levelControl);
			createdControl = levelControl;
			QPixmap pixmap(directoryForConfigs.absolutePath() + element.attribute(globalVar.strings.value("controlLvlImg")));
			if(pixmap.isNull()) {
				pixmap.load(globalVar.strings.value("default nextLvlImg"));
			}
			levelControl->setPixmap(pixmap);
			setUnionParamForBaseGraphControl(element, modelConfigs, levelControl);
		}
	}
	return createdControl;
}

void FileWorker::setUnionParamForBaseGraphControl(const QDomElement& element, const ModelConfigs& modelConfigs, ControlBaseGraphObject* graphicsObject) {
	Q_UNUSED(modelConfigs)
	graphicsObject->setObjectName(element.attribute(globalVar.strings.value("controlName")));
	QPointF gaines = graphicsObject->calculateGaines(globalVar.graphicsViewSize.width(), globalVar.graphicsViewSize.height());
	qreal controlPosX = element.attribute(globalVar.strings.value("controlPosX")).toDouble() * gaines.x();
	qreal controlPosY = element.attribute(globalVar.strings.value("controlPosY")).toDouble() + 54/gaines.y();
	if(controlPosY > 0) {
		controlPosY *= gaines.y();
	}
	graphicsObject->setPos(controlPosX, controlPosY);
	graphicsObject->setRealPos(gaines.x(), gaines.y());
}

ModelConfigs FileWorker::readConfigs(QFileInfo ConfigsFile) {
	Q_UNUSED(ConfigsFile)
	ModelConfigs modelConfigs;
	/*QFile file(ConfigsFile.absoluteFilePath());
	if(file.open(QFile::ReadOnly | QFile::Text)) {
		QDomDocument domDoc;
		if(domDoc.setContent(&file)) {
			QDomElement domElement = domDoc.documentElement();
			if(!domElement.isNull() && (domElement.nodeName() == globalVar.strings.value("configsFile"))) {
				for(QDomNode nodeChild = domElement.firstChild(); !nodeChild.isNull(); nodeChild = nodeChild.nextSibling()) {
					QDomElement element = nodeChild.toElement();
					QString elementName = element.nodeName();
					if(elementName == globalVar.strings.value("windiwWidth")) {
						int winWidth = element.attribute(globalVar.strings.value("configValue")).toUInt();
						if(winWidth >= globalVar.mainWindowMinSize.width()) {
							modelConfigs.windowWidth = winWidth;
						}
					}else if(elementName == globalVar.strings.value("windiwHeight")) {
						int winHeight = element.attribute(globalVar.strings.value("configValue")).toUInt();
						if(winHeight >= globalVar.mainWindowMinSize.height()) {
							modelConfigs.windowHeight = winHeight;
						}
					}
				}
			}
		}
		file.close();
	}*/
	return modelConfigs;
}
