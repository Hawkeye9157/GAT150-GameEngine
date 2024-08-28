#include "Object.h"

void Object::read(const json_t& value)
{
	READ_DATA(value, name);
	READ_DATA(value, isActive);
	READ_DATA(value, persistent);
}

void Object::Write(json_t& value)
{

}
