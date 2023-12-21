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
	position.x += deltaTime*10;
	position.y += deltaTime * 2;
}
