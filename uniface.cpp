#include "uniface.h"

UniFace::UniFace(QObject* parent):
	QObject(parent) {
	graphicsView = new QGraphicsView();
	graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

UniFace::~UniFace() {
	if(!graphicsView.isNull()) {
		graphicsView->deleteLater();
	}

	foreach (QGraphicsScene* scene, interfacesModel) {
		scene->deleteLater();
	}
}

void UniFace::setNewModel(QList<QGraphicsScene*> model, ModelConfigs modelConfigs) {
	if(modelConfigs.targetObjectPtr == (size_t*)this) {
		foreach (QGraphicsScene* scene, interfacesModel) {
			scene->deleteLater();
		}
		interfacesModel.clear();

		interfacesModel = model;
		changeScene(interfacesModel.at(0));
	}
}

void UniFace::resize() {
	QPointF gaines = ControlBaseGraphObject::calculateGaines(globalVar.mainWindowSize.width(), globalVar.mainWindowSize.height());
	foreach(QGraphicsItem* item, graphicsView->items()) {
		ControlBaseGraphObject* graphObj = dynamic_cast<ControlBaseGraphObject*>(item);
		if(graphObj) {
			graphObj->setPosAtView(gaines.x(), gaines.y());
		}
	}
}

void UniFace::changeScene(QGraphicsScene* scene) {
	QPointF gaines = ControlBaseGraphObject::calculateGaines(globalVar.mainWindowSize.width(), globalVar.mainWindowSize.height());
	foreach (QGraphicsScene* sceneInModel, interfacesModel) {
		if(sceneInModel == scene) {
			if(scene != graphicsView->scene()) {
				graphicsView->setScene(scene);
				foreach(QGraphicsItem* item, graphicsView->items()) {
					ControlBaseGraphObject* graphObj = dynamic_cast<ControlBaseGraphObject*>(item);
					if(graphObj) {
						graphObj->setPosAtView(gaines.x(), gaines.y());
						connect(graphObj, SIGNAL(goToLinkedScene(QGraphicsScene*)), this, SLOT(changeScene(QGraphicsScene*)), Qt::UniqueConnection);
					}
				}
			}
			break;
		}
	}
}
