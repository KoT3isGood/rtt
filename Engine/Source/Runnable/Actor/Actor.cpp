#include "Actor.h"

Actor::Actor()
{
	Register(position);
	Register(rotation);
	Register(size);
}

void Actor::EventBegin()
{
}

void Actor::EventEnd()
{
}

void Actor::EventTick(float deltaTime)
{
}
