#include "TestFile.h"


TestActor::TestActor()
{
	// here should be code for reflectancy
	classClassName = typeid(this).name();
	className = "TestActor";

	Register(customInt);
	Register(customFloat);
	Register(customString);
	Register(customVector2);
	Register(customVector3);
	Register(customVector4);

	// now normal code part


	customInt = 1;
	customFloat = 2.0;




	Construct();
}

void TestActor::Construct()
{
	testMesh = Mesh();


	size = vec3(1.0);
	testMesh.size = vec3(1.0);
	testMesh.loadFromFile("cube.obj");

	components.push_back(&testMesh);
}

void TestActor::EventEnd()
{
}

void TestActor::EventTick(float deltaTime)
{
	rotation.x += deltaTime;
}
