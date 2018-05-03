#include "controlbasegraphobject.h"
#include <QDebug>

ControlBaseGraphObject::ControlBaseGraphObject(QGraphicsItem* parent):
	QGraphicsObject(parent) {
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

ControlBaseGraphObject::~ControlBaseGraphObject() {

}

void ControlBaseGraphObject::setPixmap(const QPixmap& pixmap) {
	this->pixmap = pixmap;
}

void ControlBaseGraphObject::setRealPos(qreal gainX, qreal gainY) {
	realX = x() / gainX;
	realY = y();
	if(realY > 0) {
		realY /= gainY;
	}
	realY -= 54/gainY;
}

void ControlBaseGraphObject::setRealPos(uint windowWidth, uint windowHeight) {
	QPointF gaines = calculateGaines(windowWidth, windowHeight);
	setRealPos(gaines.x(), gaines.y());
}

void ControlBaseGraphObject::setPosAtView(qreal gainX, qreal gainY) {
	qreal newPosX = realX * gainX;
	qreal newPosY = realY + 54/gainY;
	if(newPosY > 0) {
		newPosY *= gainY;
	}
	setPos(newPosX, newPosY);
}

void ControlBaseGraphObject::setPosAtView(uint windowWidth, uint windowHeight) {
	QPointF gaines = calculateGaines(windowWidth, windowHeight);
	setPosAtView(gaines.x(), gaines.y());
}

QPointF ControlBaseGraphObject::calculateGaines(uint windowWidth, uint windowHeight) {
	return QPointF((qreal)windowWidth / 100, (qreal)windowHeight / 112);
}

QRectF ControlBaseGraphObject::boundingRect() const {
	return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void ControlBaseGraphObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->drawPixmap(QRectF(0, 0, pixmap.width(), pixmap.height()), pixmap, QRectF());
}

void ControlBaseGraphObject::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	QGraphicsObject::mousePressEvent(event);
}

void ControlBaseGraphObject::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	if(event->button() == Qt::LeftButton) {
		setRealPos((uint)globalVar.graphicsViewSize.width(), (uint)globalVar.graphicsViewSize.height());
	}
	QGraphicsObject::mouseReleaseEvent(event);
}
