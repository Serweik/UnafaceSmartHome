#include "levelcontrol.h"

LevelControl::LevelControl(QGraphicsItem* parent):
	ControlBaseGraphObject(parent) {

}

LevelControl::~LevelControl() {

}

void LevelControl::setLinkToScene(QGraphicsScene* scene) {
	linkedScene = scene;
}

QGraphicsScene*LevelControl::getLinkedScene() {
	return linkedScene;
}

void LevelControl::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	if(event->button() == Qt::LeftButton) {
		emit goToLinkedScene(linkedScene);
	}
	ControlBaseGraphObject::mouseReleaseEvent(event);
}
