#pragma once
#include "Runnable/Actor/Actor.h"

#include "Runnable/Component/Mesh.h"

class TestActor: public Actor {
public:
	TestActor();
	void Construct() override;
	void EventEnd() override;
	void EventTick(float deltaTime) override;
private:
	int customInt;
	float customFloat;
	std::string customString;

	vec2 customVector2;
	vec3 customVector3;
	vec4 customVector4;
	Mesh testMesh;
};