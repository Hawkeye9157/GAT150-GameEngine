#pragma once
#include <string>
class Object {
public:

	Object() = default;
	Object(const std::string& name) : name{name} {}

	virtual void Initialize() = 0;
	virtual void Activate() { isActive = true; }
	virtual void Deactivate() { isActive = false; }

public:

	std::string name = NULL;
	bool isActive{false};
};
