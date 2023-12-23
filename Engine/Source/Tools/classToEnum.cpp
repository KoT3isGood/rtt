#include "classToEnum.h"

classType getClassTypeFromString(std::string className)
{
	
	if (className == "int") {
		return integer;
	}
	if (className == "float") {
		return floating;
	}
	if (className == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
		return stringData;
	}
	if (className == "struct glm::vec<2,float,0>") {
		return vector2;
	}
	if (className == "struct glm::vec<3,float,0>") {
		return vector3;
	}
	if (className == "struct glm::vec<4,float,0>") {
		return vector4;
	}

	return noneVar;
};