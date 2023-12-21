#include "CurrentProperties.h"
#include "Runtime/Engine/Tokenizer/Tokenizer.cpp"
#include "Runnable/Actor/Actor.cpp"
#include "Runnable/Component/Component.cpp"
#include "Runnable/Component/Mesh.cpp"
#include "Tools/Logger.cpp"
#include "Tools/rttmath.cpp"

World currentWorld = World();

void SpawnActorTest() {
	TestActor* test = new TestActor();
	currentWorld.SpawnActor(test);
};

World* GetWorld()
{
	return &currentWorld;
}
