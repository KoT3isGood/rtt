#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string fileDirectory, std::vector<std::string> bannedTokens, bool includeBannedCharacters)
{
	currentCharacter = 0;
	std::string myText;
	std::string fileContext = "";

	std::ifstream MyReadFile(fileDirectory);
	if (MyReadFile.good()) {
		// Use a while loop together with the getline() function to read the file line by line
		while (std::getline(MyReadFile, myText)) {
			// Output the text from the file
			fileContext += myText + "\n";
			//PRINT(myText);
		}
		// Close the file
		MyReadFile.close();

		while (currentCharacter <= size(fileContext) - 2) {
			std::string token = getNextToken(&fileContext, &bannedTokens, &includeBannedCharacters);
			if (token != "") {
				tokens.push_back(token);
			}
		};
	}
	else {
		PRINTADVANCED("Failed to find file "+fileDirectory, error);
	}
}
Tokenizer::Tokenizer(std::string fileDirectory, std::vector<std::string> bannedTokens, std::vector<std::string> totallyBannedTokens)
{
	currentCharacter = 0;
	std::string myText;
	std::string fileContext = "";

	std::ifstream MyReadFile(fileDirectory);
	if (MyReadFile.good()) {
		// Use a while loop together with the getline() function to read the file line by line
		while (std::getline(MyReadFile, myText)) {
			// Output the text from the file
			fileContext += myText + "\n";
			//PRINT(myText);
		}
		// Close the file
		MyReadFile.close();

		while (currentCharacter <= size(fileContext) - 2) {
			std::string token = getNextToken(&fileContext, &bannedTokens, &totallyBannedTokens);
			if (token != "") {
				tokens.push_back(token);
			}
			
		};
	}
	else {
		PRINTADVANCED("Failed to find file " + fileDirectory, error);
	}
}
Tokenizer::Tokenizer(std::string text, std::vector<std::string> bannedTokens, bool includeBannedCharacters, bool ignore)
{
	currentCharacter = 0;
	std::string myText;
	std::string fileContext = text;

	while (currentCharacter <= size(fileContext) - 2) {
		tokens.push_back(getNextToken(&fileContext, &bannedTokens, &includeBannedCharacters));
	};
}

std::string Tokenizer::getNextToken(std::string* text, std::vector<std::string>* bannedTokens, bool* includeBannedCharacters)
{
	std::string token = "";
	std::string val = "";
	int starterVal = currentCharacter;

	for (int i = currentCharacter; i < size(*text); i++) {

		char name = char(text->at(currentCharacter)) + 0;
		val = name;
		if (std::find(bannedTokens->begin(), bannedTokens->end(), val) != bannedTokens->end()) {
			if (currentCharacter == starterVal) {
				if (*includeBannedCharacters) {
					token += val;
				}
				else {

				}


			}
			currentCharacter += 1;

			break;
		}
		token += val;
		currentCharacter += 1;
	}
	return token;
}

std::string Tokenizer::getNextToken(std::string* text, std::vector<std::string>* bannedTokens, std::vector<std::string>* totallyBannedTokens)
{
	std::string token = "";
	std::string val = "";
	int starterVal = currentCharacter;

	for (int i = currentCharacter; i < size(*text); i++) {
		char name = char(text->at(currentCharacter)) + 0;
		val = name;
		if (std::find(bannedTokens->begin(), bannedTokens->end(), val) != bannedTokens->end()) {
			if (currentCharacter == starterVal) {
				if (std::find(totallyBannedTokens->begin(), totallyBannedTokens->end(), val) != totallyBannedTokens->end()) {
					
				}
				else {
					token += val;
					
				}
				currentCharacter += 1;
			}


			break;
		}
		token += val;

		currentCharacter += 1;
		
	}
	return token;
}
