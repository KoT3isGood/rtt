#include "Logger.h"
#ifdef ENABLED
void logData(std::string data, LogType errortype, std::string callerFunction, std::string callerFile, int Line) {
	std::string _data = data;


	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%X", &tstruct);






	std::string str;
	switch (errortype) {
	case none:
		str = "======== RETTO [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			"; " +
			_data +
			"\n";
		break;
	case info:
		str = "======== RETTO [ INFO ] [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			"; " +
			_data +
			"\n";
		break;
	case ok:
		str = "======== RETTO [ OK ] [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			"; " +
			_data +
			"\n";
		break;

	case glsl:
		str = "======== RETTO [ GLSL ] [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			"; " +
			_data +
			"\n";
		break;
	case glslerror:
		str = "======== RETTO [ GLSL ERROR ] [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			" in " +
			callerFile +
			": line " +
			std::to_string(Line) +
			" ] " +
			_data +
			"\n";
		break;
	case warning:
		str = "======== RETTO [ WARNING ] [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			" in " +
			callerFile +
			": line " +
			std::to_string(Line) +
			" ] " +
			_data +
			"\n";
		break;
	case error:
		str = "======== RETTO [ ERROR ] [ " +
			std::string(buf) +
			" ] " +
			callerFunction +
			" in " +
			callerFile +
			": line " +
			std::to_string(Line) +
			" ] " +
			_data +
			"\n";
		break;
	}
	std::wstring temp = std::wstring(str.begin(), str.end());
	LPCWSTR wideString = temp.c_str();
	OutputDebugStringW(wideString);
}

#endif

void criticalError(std::string message, std::string title)
{
	std::string str1 = message;
	std::wstring temp1 = std::wstring(str1.begin(), str1.end());
	LPCWSTR wideString1 = temp1.c_str();

	std::string str2 = title;
	std::wstring temp2 = std::wstring(str2.begin(), str2.end());
	LPCWSTR wideString2 = temp2.c_str();
	MessageBoxW(NULL, wideString1, wideString2, MB_ICONERROR | MB_OK);
}