#ifndef BYTEBUTTON_H
#define BYTEBUTTON_H

#include "controlbasegraphobject.h"

class ByteButton: public ControlBaseGraphObject {
	Q_OBJECT
	public:
		explicit ByteButton(QGraphicsItem* parent = Q_NULLPTR);
		virtual ~ByteButton();
};

#endif // BYTEBUTTON_H
