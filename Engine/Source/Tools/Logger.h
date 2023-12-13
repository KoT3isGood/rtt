#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <assert.h>


#ifdef ENABLED


enum LogType
{
	none,
	info,
	ok,
	glsl,
	warning,
	error,
	glslerror,
};


void logData(std::string data, LogType errortype = none, std::string callerFunction = "", std::string callerFile = "", int Line = 0);



// DO NOT USE IN EVENT TICK!!!
#define PRINTADVANCED(x,y) logData(x,y,__FUNCTION__,__FILE__,__LINE__)
#define PRINT(x) logData(x,none,__FUNCTION__,__FILE__,__LINE__)

#else
#define PRINT(...)
#define PRINTADVANCED(...)
#endif
void criticalError(std::string message, std::string title);
#define CRITICALERROR criticalError


#define spacer std::string("   ")