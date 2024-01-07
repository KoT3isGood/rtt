#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Tools/Logger.h"
#include "Engine/glm/glm.hpp"
using namespace glm;

// DLL export engine macro
#define FUNC extern "C" _declspec(dllexport)


/*
 * Use this to mark your Actor as reflected.
 * If you build your project using Shift+B nothing will be generated.
 * You have to use Build Button in ReTTo to generate variables.
 * Make sure it is in front of the Actor's opening.
 * Like this: class XXX: public Reflectable { REFLECTACTOR();
*/
#define REFLECTACTOR() public: void RegisterVariables() override; private:

/*
 * Use this to mark your Component as reflected.
 * If you build your project using Shift+B nothing will be generated.
 * You have to use Build Button in ReTTo to generate variables.
 * Make sure it is in front of the Component's opening.
 * Like this: class XXX: public Reflectable { REFLECTACTOR();
*/
#define REFLECTCOMPONENT() public: void RegisterVariables() override; private: