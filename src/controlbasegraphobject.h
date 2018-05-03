#ifndef CONTROLBASEGRAPHOBJECT_H
#define CONTROLBASEGRAPHOBJECT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

#include "globalvariables.h"

class ControlBaseGraphObject: public QGraphicsObject {
		Q_OBJECT
		public:
			explicit ControlBaseGraphObject(QGraphicsItem* parent = Q_NULLPTR);
			virtual ~ControlBaseGraphObject();

			void setPixmap(const QPixmap& pixmap);
			void setRealPos(qreal gainX, qreal gainY);
			void setRealPos(uint windowWidth, uint windowHeight);
			void setPosAtView(qreal gainX, qreal gainY);
			void setPosAtView(uint windowWidth, uint windowHeight);
			static QPointF calculateGaines(uint windowWidth, uint windowHeight);

		signals:
			void goToLinkedScene(QGraphicsScene* scene);	//для контролов, управляющих переходами по уровням

		protected:
			virtual QRectF boundingRect() const;
			virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

			virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
			//virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
			virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
			//virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

		private:
			qreal realX;
			qreal realY;
			QPixmap pixmap;
	};

#endif // CONTROLBASEGRAPHOBJECT_H
