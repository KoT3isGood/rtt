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
 * Use this to mark your class as reflected.
 * If you build your project using Shift+B nothing will be generated.
 * You have to use Build Button in ReTTo to generate variables.
 * Make sure it is in front of the class opening.
 * Like this: class XXX: public Reflectable { REFLECTCLASS();
*/
#define REFLECTCLASS() public: void RegisterVariables() override; private: