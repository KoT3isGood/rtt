#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Tools/Logger.h"

class Tokenizer {
public:

	Tokenizer(std::string fileDirectory, std::vector<std::string> bannedTokens, bool includeBannedCharacters);
	Tokenizer(std::string text, std::vector<std::string> bannedTokens, bool includeBannedCharacters, bool ignore);
	std::vector<std::string> tokens;
private:
	int currentCharacter = 0;
	std::string getNextToken(std::string* text, std::vector<std::string>* bannedTokens, bool* includeBannedCharacters);
};