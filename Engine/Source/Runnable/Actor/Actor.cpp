#include "Actor.h"

Actor::Actor()
{
	Register(position);
	Register(rotation);
	Register(size);
}

void Actor::Construct()
{
	return;
}

void Actor::EventEnd()
{
	return;
}

void Actor::EventTick(float deltaTime)
{
	return;
}
