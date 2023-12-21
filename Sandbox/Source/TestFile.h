#pragma once
#include "Runnable/Actor/Actor.h"

#include "Runnable/Component/Mesh.h"

class TestActor: public Actor {
public:
	TestActor();
	void EventBegin() override;
	void EventEnd() override;
	void EventTick(float deltaTime) override;

	Mesh testMesh = Mesh();
};