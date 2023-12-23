#include "CurrentProperties.h"
#include "Runtime/Engine/Tokenizer/Tokenizer.cpp"
#include "Runnable/Actor/Actor.cpp"
#include "Runnable/Component/Component.cpp"
#include "Runnable/Component/Mesh.cpp"
#include "Tools/Logger.cpp"
#include "Tools/rttmath.cpp"
#include "Runnable/Reflected.cpp"
#include "Tools/classToEnum.cpp"


World currentWorld = World();

void SpawnActorTest() {
	currentWorld.SpawnActor(new TestActor());
};

World* GetWorld()
{
	return &currentWorld;
}


World* GetWorldCopy()
{
	World* newWorld = new World(*GetWorld());

	std::vector<Actor*> newActors = {};

	// Since world points to the same actor i should generate new ones
	for (auto actor : newWorld->actors) {
		newActors.push_back(dynamicCastFromClass(actor));
	};
	newWorld->actors = newActors;
	return newWorld;
}