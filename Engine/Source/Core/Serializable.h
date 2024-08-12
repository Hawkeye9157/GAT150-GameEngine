#pragma once
#include "Json.h"

class Serializable {
public:
	virtual ~Serializable() = default;

	virtual void read(const json_t& value) = 0;
	virtual void Write( json_t& value) = 0;

private:
};