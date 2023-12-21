#pragma once
#include "EngineMacros.h"
#include "Runnable/Actor/Actor.h"
#include "Tools/rttmath.h"
#include "Runnable/Component/Mesh.h"
class World
{
public:
	World() = default;
	World(std::string worldName);
	void SpawnActor(Actor* actor);
	void UpdateWorld(float deltaTime);
	std::vector<Actor*> actors = {};
	void PrecalculateTriangles();
	std::vector<float>* GetWorldGeometry();
	std::vector<float>* GetBoundingBoxes();
private:
	std::vector<float> worldGeometry = {};
	std::vector<float> boundingBoxes = {};
};