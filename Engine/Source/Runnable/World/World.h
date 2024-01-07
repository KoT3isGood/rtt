#pragma once
#include "EngineMacros.h"
#include "Runnable/Actor/Actor.h"
#include "Tools/rttmath.h"
#include "Runnable/Component/Mesh.h"
#include "Runnable/Component/SubComponents/LightComponent.h"
#include "Tools/classToEnum.h"
#include <sstream>
#include "PlayerController.h"

class World
{
public:
	World() = default;
	void SerializeWorld(std::string path, std::string name);

	PlayerController currentPlayerController;

	void SpawnActor(Actor* actor);
	void StartRunningWorld();
	void UpdateWorld(float deltaTime);
	std::vector<Actor*> actors = {};
	void PrecalculateTriangles();
	std::vector<float>* GetWorldLights();
	std::vector<float>* GetWorldGeometry();
	std::vector<float>* GetBoundingBoxes();

	bool isTickingEnabled = false;

private:
	std::vector<float> worldGeometry = {};
	std::vector<float> boundingBoxes = {};
	std::vector<float> lights = {};
};