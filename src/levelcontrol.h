#ifndef LEVELCONTROL_H
#define LEVELCONTROL_H

#include <QGraphicsScene>

#include "controlbasegraphobject.h"

class LevelControl: public ControlBaseGraphObject {
	Q_OBJECT
	public:
		explicit LevelControl(QGraphicsItem* parent = Q_NULLPTR);
		virtual ~LevelControl();

		void setLinkToScene(QGraphicsScene* scene);
		QGraphicsScene* getLinkedScene();

	protected:
		virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	private:
		QGraphicsScene* linkedScene = nullptr;
};

#endif // LEVELCONTROL_H
