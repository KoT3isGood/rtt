#include "TestFile.h"


TestActor::TestActor()
{
	
	testMesh.loadFromFile("cube.obj");
	components.push_back(&testMesh);
}

void TestActor::EventBegin()
{
}

void TestActor::EventEnd()
{
}

void TestActor::EventTick(float deltaTime)
{
	rotation.x += deltaTime;
}
