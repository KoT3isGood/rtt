#pragma once
#include "EngineMacros.h"

#define getClassOf(x) typeid(x).name()
#define Register(x) RegisterVariable(#x,getClassOf(x),&x)
class Reflected {
public:
	void RegisterVariable(std::string varName,std::string varClass,void* varPtr);
	std::vector<std::string> variableRegistryNames;
	std::vector<void*> variableRegistry;
	std::vector<std::string> variableRegistryClass;
};