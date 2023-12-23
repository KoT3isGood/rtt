#pragma once
#include "EngineMacros.h"
#include "Runnable/Actor/Actor.h"
#include "Tools/rttmath.h"
#include "Runnable/Component/Mesh.h"
#include "Tools/classToEnum.h"
class World
{
public:
	World() = default;
	World(std::string worldName);

	void SerializeWorld(std::string path, std::string name);

	void SpawnActor(Actor* actor);
	void UpdateWorld(float deltaTime);
	std::vector<Actor*> actors = {};
	void PrecalculateTriangles();
	std::vector<float>* GetWorldGeometry();
	std::vector<float>* GetBoundingBoxes();

	bool isTickingEnabled = false;
private:
	std::vector<float> worldGeometry = {};
	std::vector<float> boundingBoxes = {};
};