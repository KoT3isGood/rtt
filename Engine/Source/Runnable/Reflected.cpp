#include "Reflected.h"

void Reflected::RegisterVariables()
{
}

void Reflected::RegisterVariable(std::string varName, std::string varClass, void* varPtr)
{
	variableRegistryNames.push_back(varName);
	variableRegistryClass.push_back(varClass);
	variableRegistry.push_back(varPtr);
}

int Reflected::TryToFindVariableByName(std::string variable)
{
	for (int i = 0; i < variableRegistryNames.size(); i++) {
		if (variableRegistryNames[i] == variable) {
			return i;
		};
	}
	return -1;
}
