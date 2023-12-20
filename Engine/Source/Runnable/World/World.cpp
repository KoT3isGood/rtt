#include "World.h"

World::World(std::string worldName)
{
}

void World::SpawnActor(Actor* actor)
{
	actors.push_back(actor);
}

void World::UpdateWorld(float deltaTime)
{
	for (Actor* actor : actors) {
		actor->EventTick(deltaTime);
	};
}
