#include "Object.h"

void Object::read(const json_t& value)
{
	READ_DATA(value, name);
	//READ_DATA(value, isActive);
}

void Object::Write(json_t& value)
{

}
