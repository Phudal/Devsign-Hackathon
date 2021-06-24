#include "Object.h"

CObject::CObject()  { }
CObject::~CObject() { }

tstring CObject::ToString() const
{
	return ToTString(typeid(*this).name());
}
