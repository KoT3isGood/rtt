#pragma once
#include "EngineMacros.h"
#include "Runnable/Actor/Actor.h"
class World
{
public:
	World() = default;
	World(std::string worldName);
	void SpawnActor(Actor* actor);
	void UpdateWorld(float deltaTime);
private:
	std::vector<Actor*> actors = {};
};

