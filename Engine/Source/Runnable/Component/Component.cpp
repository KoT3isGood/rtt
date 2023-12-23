#include "Component.h"

Component::Component() {
	Register(position);
	Register(rotation);
	Register(size);
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
