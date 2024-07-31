#include "EAssert.h"

#include <iostream>

void CustomAssert(const std::string& expression, const std::string filename, int line)
{
	std::cerr << "Asseretion Failed: (" << expression << "), File: " << filename << ", Line: " << line << std::endl;
	std::abort();
}
