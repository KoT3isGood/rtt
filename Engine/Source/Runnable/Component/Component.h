#pragma once
#include "EngineMacros.h"
#include "Runnable/Reflected.h"
class Component : public Reflected {
	REFLECTCLASS();
public:
	// Serialization
	std::string classClassName = "";
	std::string className = "";

	Component();
	virtual void EventBegin();
	virtual void EventEnd();
	virtual void EventTick(float deltaTime);

	vec3 position = vec3(0.0);
	vec3 rotation = vec3(0.0);
	vec3 size = vec3(1.0);
};