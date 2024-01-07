#pragma once
#include "EngineMacros.h"

// Returns classname of variable
#define getClassOf(x) typeid(x).name()
// Registrates variable inside of class
#define Register(x) RegisterVariable(#x,getClassOf(x),&x)

// Used for reflection of classes
class Reflected {
public:
	virtual void RegisterVariables();
	void RegisterVariable(std::string varName,std::string varClass,void* varPtr);
	int TryToFindVariableByName(std::string variable);
	std::vector<std::string> variableRegistryNames;
	std::vector<void*> variableRegistry;
	std::vector<std::string> variableRegistryClass;
};