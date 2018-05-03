#ifndef UNIVERSALFACTORY_H
#define UNIVERSALFACTORY_H

#include "bytebutton.h"
#include "levelcontrol.h"

class UniversalFactory{
	public:
		template<class TypeObjects>
			static TypeObjects* createObject(TypeObjects* oblectPointer = nullptr);

	private:
		UniversalFactory() = delete;
};

template<class TypeObjects>
TypeObjects* UniversalFactory::UniversalFactory::createObject(TypeObjects* oblectPointer) {
	oblectPointer = new TypeObjects();
	return oblectPointer;
}

#endif // UNIVERSALFACTORY_H
