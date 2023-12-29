#include "Reflector.h"



void BuildReflectedGame(GameLoader* game)
{
	std::string regDirectory = game->currentGamePath + "/Bridge/Generated/ClassRegistry.gen.h";
	const char* registryDirectory = regDirectory.c_str();
	std::ofstream classRegistry(registryDirectory);

	std::string instDirectory = game->currentGamePath + "/Bridge/Generated/Inst.gen.cpp";
	const char* instanciateDirectory = instDirectory.c_str();
	std::ofstream classInstRegistry(instanciateDirectory);

	std::string dyncDirectory = game->currentGamePath + "/Bridge/Generated/DynCast.gen.cpp";
	const char* dynamicCastDirectory = dyncDirectory.c_str();
	std::ofstream dynCast(dynamicCastDirectory);

	classRegistry.clear();
	classInstRegistry.clear();
	dynCast.clear();



	dynCast << R"(
#include "Inst.h"
#include "Generated/ClassRegistry.gen.h"
#define GenerateActor(x) Actor* var = new x(*dynamic_cast<x*>(actor)); var->RegisterVariables();for(auto component:var->components){component->RegisterVariables();}; return var
Actor* dynamicCastFromClass(Actor * actor)
{
std::string classClassName = actor->className; 
)";

classInstRegistry << R"(
#include "Inst.h"
#include "Generated/ClassRegistry.gen.h"
)";

	for (auto& p : std::filesystem::recursive_directory_iterator(game->currentGamePath + "/Source")) {
		auto path = p.path();
		std::string pathStr = path.string();
		if (!std::filesystem::is_directory(path)) {
			std::cout << pathStr << "\n";

			std::vector<ClassObject> classes = {};
			if (pathStr[pathStr.size() - 1] == 'h' && pathStr[pathStr.size() - 2] == '.') {
				ReflectHeader(pathStr, &classes);
				PRINT(std::filesystem::relative(pathStr, game->currentGamePath + "/Source").string());
				classRegistry << R"(#include ")" << std::filesystem::relative(pathStr, game->currentGamePath + "/Source").string() << R"(")" << "\n";

				for (int currentclass = 0; currentclass < classes.size(); currentclass++) {
					if (classes[currentclass].shouldBeReflected) {
						
						dynCast << R"(if (classClassName == ")" << classes[currentclass].name << R"(") {)" << "GenerateActor("<< classes[currentclass].name<<");};";




						classInstRegistry << "void " << classes[currentclass].name << "::RegisterVariables() {" << "\n";
						classInstRegistry << "variableRegistryNames = {};" << "\n";
						classInstRegistry << "variableRegistry = {};" << "\n";
						classInstRegistry << "variableRegistryClass = {};" << "\n";
						classInstRegistry << "classClassName = typeid(this).name();" << "\n";
						classInstRegistry << R"(className = ")" << classes[currentclass].name << R"(";)" << "\n";
						classInstRegistry << "Register(position);" << "\n";
						classInstRegistry << "Register(rotation);" << "\n";
						classInstRegistry << "Register(size); " << "\n";
						for (int currentVar = 0; currentVar < classes[currentclass].variables.size();currentVar++) {
							classInstRegistry << "Register(" << classes[currentclass].variables[currentVar] << ");" << "\n";
						};
						classInstRegistry << "};" << "\n";
					}
					
				}
			};
		}
		
	};

	dynCast << R"(	
actor->RegisterVariables();
return new Actor(*actor);
})";
	classRegistry.close();
	classInstRegistry.close();
	dynCast.close();

	std::string gamepath = game->currentGame;
	std::string gameName = gamepath;
	gameName = gameName.erase(gameName.size()-3, gameName.size() - 1);
	gameName += "vcxproj";
	PRINT(gameName);
	game->KillDll();
	std::string commandName = "msbuild " + gameName + " /p:Configuration=Debug /p:Platform=x64";
	const char* command = commandName.c_str();
	int result = std::system(command);
	PRINT(gamepath);
	game->UpdateDll(gamepath);






}

bool ReflectHeader(std::string path, std::vector<ClassObject>* classesOutput) {

	std::vector<std::string> bannedTokens = {"\n"," ",":",";","{","}","(",")","=","*","&","	"};
	std::vector<std::string> totallyBannedTokens = {"\n"," ","	" };

	Tokenizer tokenizedFile = Tokenizer(path, bannedTokens, totallyBannedTokens);

	std::vector<ClassObject> Classes = {};

	int currentClass = -1;
	for (int currentToken = 0; currentToken < tokenizedFile.tokens.size(); currentToken++) {
		std::string tokenData = tokenizedFile.tokens[currentToken];
		//PRINT(tokenData);

		if (tokenData == "class") {
			currentToken += 1;
			currentClass += 1;
			std::string className = tokenizedFile.tokens[currentToken];
			PRINT("class " + className);
			ClassObject newClass = ClassObject();
			newClass.shouldBeReflected = false;
			newClass.name = className;
			
			
			// Find a class with code validation
			while (currentToken < tokenizedFile.tokens.size() - 1) {
				currentToken += 1;
				std::string newToken = tokenizedFile.tokens[currentToken];
				if (newToken == "{") {
					PRINT("Found { ");
					std::string newToken = tokenizedFile.tokens[currentToken];
					break;
				};
				// Protection system
				if (newToken == ";") {
					currentToken = tokenizedFile.tokens.size(); break;
				};
				// Protection system
				if (newToken == "}") {
					currentToken = tokenizedFile.tokens.size(); break;
				};
				// Protection system
				if (newToken == "class") {
					currentToken = tokenizedFile.tokens.size(); break;
				};
			};
			if (currentToken == tokenizedFile.tokens.size()) {
				PRINTADVANCED(R"(C++: Failed to find '{' of class ")" + className + R"(" '{'. Project will not be compiled)", error); return false;
			};

			// Find REFLECTCLASS
			bool isStartingToken = true;
			while (currentToken < tokenizedFile.tokens.size() - 1) {
				currentToken += 1;
				std::string newToken = tokenizedFile.tokens[currentToken];
				PRINT(newToken);
				if (newToken == "REFLECTCLASS" && isStartingToken == true) {
					PRINTADVANCED(R"(WhatTheHeader: Found REFLECTCLASS)", info);
					newClass.shouldBeReflected = true;
					break;
				}
				else {
					isStartingToken = false;
					if (newToken == "REFLECTCLASS") {
						PRINTADVANCED(R"(WhatTheHeader: Found REFLECTCLASS)", info);
						PRINTADVANCED(R"(WhatTheHeader: REFLECTCLASS is not in the start of the class ")" + className + R"(". Class will not be included in the reflection)", error);
						PRINTADVANCED(R"(WhatTheHeader: To fix this you can move REFLECTCLASS() to the start of the class)", error);
						break;
					}

				};

			}
			Classes.push_back(newClass);
		}
		

		if (currentClass != -1) {
			// Find Variables
			while (currentToken < tokenizedFile.tokens.size() - 3) {
				
				currentToken += 1;
				std::string newToken = tokenizedFile.tokens[currentToken];
				
				if (newToken == ";") {
					// verify if it is a function
					std::string possibleVarName;
					int currentTokenCpy = currentToken;
					bool isFirstIter = false;
					while (currentTokenCpy >0) {
						currentTokenCpy -= 1;
						if (tokenizedFile.tokens[currentTokenCpy] == ":") {
							currentTokenCpy -= 1;
							break;
						}
						if (tokenizedFile.tokens[currentTokenCpy] == ";") {
							break;
						}
						if (tokenizedFile.tokens[currentTokenCpy] == "default") {
							currentTokenCpy -= 1;
							break;
						}
						if (tokenizedFile.tokens[currentTokenCpy] == "override") {
							currentTokenCpy -= 1;
							break;
						}
						if (tokenizedFile.tokens[currentTokenCpy] == ")") {
							currentTokenCpy -= 1;
							break;
						}
						if (tokenizedFile.tokens[currentTokenCpy] == "=") {
							currentTokenCpy -= 1;
							possibleVarName = tokenizedFile.tokens[currentTokenCpy];
							
						}
						if (isFirstIter) {
							possibleVarName = tokenizedFile.tokens[currentTokenCpy+1];
						}
						isFirstIter = true;
					}
					if (possibleVarName != "") {
						Classes[currentClass].variables.push_back(possibleVarName);
					}
				}
			}
		}
	}
	*classesOutput = Classes;
	return true;
};