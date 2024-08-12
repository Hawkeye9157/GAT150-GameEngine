#include "Transform.h"

void Transform::read(const json_t& value) {
	READ_DATA(value, position);
	READ_DATA(value, rotation);
	READ_DATA(value, scale);
}

void Transform::Write(json_t& value) {

}
