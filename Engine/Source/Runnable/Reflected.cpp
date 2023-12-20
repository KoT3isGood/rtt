#include "Reflected.h"

void Reflected::RegisterVariable(std::string varName, std::string varClass, void* varPtr)
{
	variableRegistryNames.push_back(varName);
	variableRegistryClass.push_back(varClass);
	variableRegistry.push_back(varPtr);
}
