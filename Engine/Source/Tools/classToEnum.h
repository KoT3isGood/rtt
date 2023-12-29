#pragma once
#include "EngineMacros.h"
enum classType {
	noneVar,
	integer,
	booleanC,
	floating,
	stringData,
	vector2,
	vector3,
	vector4
};

classType getClassTypeFromString(std::string className);