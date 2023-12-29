#pragma once


#include <istream>
#include <ostream>
#include <filesystem>

#include "..\..\Engine\GameLoader\GameLoader.h"
#include "..\..\Engine\Tokenizer\Tokenizer.h"

struct ClassObject {
	std::string name;
	bool shouldBeReflected;
	std::vector<std::string> variables;
};

void BuildReflectedGame(GameLoader* game);

bool ReflectHeader(std::string path, std::vector<ClassObject>* classesOutput);


