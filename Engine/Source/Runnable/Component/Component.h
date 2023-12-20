#pragma once
#include "EngineMacros.h"
#include "Runnable/Reflected.h"
class Component : public Reflected {
public:
	Component();
	virtual void EventBegin();
	virtual void EventEnd();
	virtual void EventTick();

	vec3 position = vec3(0.0);
	vec3 rotation = vec3(0.0);
	vec3 size = vec3(0.0);
};