#include "Component.h"

Component::Component() {
	RegisterVariables();
};

void Component::EventBegin()
{
	return;
}

void Component::EventEnd()
{
	return;
}

void Component::EventTick(float deltaTime)
{
	return;
}

void Component::RegisterVariables() {
	variableRegistryNames = {};
	variableRegistry = {};
	variableRegistryClass = {};
	classClassName = typeid(this).name();
	className = "LightComponent";
	Register(position);
	Register(rotation);
	Register(size);
}