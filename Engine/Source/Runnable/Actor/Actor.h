#pragma once
#include "EngineMacros.h"
#include "Runnable/Reflected.h"
#include "Runnable\Component\Component.h"
#include "Runnable\Component\CameraComponent.h"
class Actor : public Reflected {
public:
	

	// Serialization
	std::string classClassName = "";
	std::string className = "";
	// Actors
	Actor();
	virtual void EventEnd();
	virtual void EventTick(float deltaTime);

	std::vector<Component*> components = {};
	CameraComponent* currentCamera = nullptr;
	bool enableAutoPoccess = false;

	vec3 position = vec3(0.0);
	vec3 rotation = vec3(0.0);
	vec3 size = vec3(1.0);
};