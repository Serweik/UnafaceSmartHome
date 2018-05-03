#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QObject>
#include <QWidget>

#include <QDir>
#include <QtXml>
#include <QFile>
#include <QTextStream>

#include <QGraphicsScene>

#include "swenum.h"
#include "universalfactory.h"
#include "globalvariables.h"

struct ModelConfigs {
	size_t* targetObjectPtr = nullptr;	// чтобы конкретезировать для какого объекта собирается модель, т.к. на 1 сигнал может подписаться несколько объектов
};

SW_ENUM (
	LoadingMode, unsigned char, unsigned char,
	TAB_MODE,
	ONE_EXEMPLAR_MODE
)

struct InterfaceConfigs {
	QSize windowSize = {800, 480};
	LoadingMode loadingMode;
};

class FileWorker: public QObject {
	Q_OBJECT
	public:
		explicit FileWorker(QObject* parent = 0);
		InterfaceConfigs readInterfaceConfigs(QString pathToConfigs);

	public slots:
		void buildModel(QString pathToConfigs, size_t* targetObjectPtr);

	signals:
		void modelBuilded(QList<QGraphicsScene*> model, ModelConfigs modelConfigs);

	private:
		enum ControlTypeBase {
			LEVELITEM,
			Q_GRAPHICS_ITEM,
			Q_WIDGET
		};

		QGraphicsScene* createScene(QList<QGraphicsScene*>& model, const ModelConfigs& modelConfigs, const QDir& directoryForConfigs, const QDomElement& domElement);
		QObject* createControl(const QDomElement& element, ControlTypeBase& controlTypeBase, const QDir& directoryForConfigs, const ModelConfigs& modelConfigs);
		void setUnionParamForBaseGraphControl(const QDomElement& element, const ModelConfigs& modelConfigs, ControlBaseGraphObject* graphicsObject);
		ModelConfigs readConfigs(QFileInfo ConfigsFile);
};

#endif // FILEWORKER_H
