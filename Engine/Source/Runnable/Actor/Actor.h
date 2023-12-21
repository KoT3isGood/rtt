#pragma once
#include "EngineMacros.h"
#include "Runnable/Reflected.h"
#include "Runnable\Component\Component.h"
class Actor : public Reflected {
public:
	Actor() = default;
	virtual void EventBegin();
	virtual void EventEnd();
	virtual void EventTick(float deltaTime);

	std::vector<Component*> components = {};

	vec3 position = vec3(0.0);
	vec3 rotation = vec3(0.0);
	vec3 size = vec3(1.0);
};