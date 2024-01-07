
#include "World.h"



void World::SpawnActor(Actor* actor)
{
	for (Component* component : actor->components) {
		component->RegisterVariables();
	}
	actors.push_back(actor);
}

void World::StartRunningWorld() {
	for (Actor* actor : actors) {
		if (actor->enableAutoPoccess) {
			currentPlayerController.ownedActor = actor;
			break;
		};
	};
}

void World::UpdateWorld(float deltaTime)
{
	if (isTickingEnabled) {
		for (Actor* actor : actors) {
			actor->EventTick(deltaTime);
			for (Component* component : actor->components) {
				component->EventTick(deltaTime);
			}
		};
	}
}

void World::PrecalculateTriangles()
{
	// TODO: Move to compute shader
	worldGeometry = {};
	boundingBoxes = {};
	lights = {};
	int totalTriangles = 0;
	for (auto actor : actors) {
		mat3x3 actorRotation = rotationToMat3x3(actor->rotation);
		vec3 actorPosition = actor->position;
		vec3 actorSize = actor->size;
		for (auto component : actor->components) {
			mat3x3 componentRotation = rotationToMat3x3(component->rotation);
			vec3 componentPosition = component->position;
			vec3 componentSize = component->size;
			if (Mesh* meshComponent = dynamic_cast<Mesh*>(component)) {
				meshComponent->modifiedVertex = meshComponent->vertex;

				int bbstart = totalTriangles;

				meshComponent->maxX = -FLT_MAX;
				meshComponent->minX = FLT_MAX;
				meshComponent->maxY = -FLT_MAX;
				meshComponent->minY = FLT_MAX;
				meshComponent->maxZ = -FLT_MAX;
				meshComponent->minZ = FLT_MAX;




				// apply transform
				for (int i = 0; i < meshComponent->modifiedVertex.size(); i++) {
					vec3* vertex = &meshComponent->modifiedVertex[i];
					*vertex = vec3(vertex->x, vertex->z, vertex->y);
					// Iteration 1: component transform
					*vertex *= componentSize;
					*vertex = componentRotation * *vertex;
					*vertex += componentPosition;
					// Iteration 1: actor transform
					*vertex *= actorSize;
					*vertex = actorRotation * *vertex;
					*vertex += actorPosition;

					// Calculate bounding boxes;
					if (vertex->x > meshComponent->maxX)
					{
						meshComponent->maxX = vertex->x;
					}
					if (vertex->x < meshComponent->minX)
					{
						meshComponent->minX = vertex->x;
					}
					//y
					if (vertex->y > meshComponent->maxY)
					{
						meshComponent->maxY = vertex->y;
					}
					if (vertex->y < meshComponent->minY)
					{
						meshComponent->minY = vertex->y;
					}
					//z
					if (vertex->z > meshComponent->maxZ)
					{
						meshComponent->maxZ = vertex->z;
					}
					if (vertex->z < meshComponent->minZ)
					{
						meshComponent->minZ = vertex->z;
					}
				}

				// generate world triangle matrix
				for (int i = 0; i < meshComponent->elementVertex.size(); i += 3) {
					int vertexID1 = meshComponent->elementVertex[i] - 1;
					int vertexID2 = meshComponent->elementVertex[i + 1] - 1;
					int vertexID3 = meshComponent->elementVertex[i + 2] - 1;
					vec3 vertex1 = meshComponent->modifiedVertex[vertexID1];
					vec3 vertex2 = meshComponent->modifiedVertex[vertexID2];
					vec3 vertex3 = meshComponent->modifiedVertex[vertexID3];

					int uvID1 = meshComponent->elementUv[i] - 1;
					int uvID2 = meshComponent->elementUv[i + 1] - 1;
					int uvID3 = meshComponent->elementUv[i + 2] - 1;
					vec2 uv1 = meshComponent->uv[uvID1];
					vec2 uv2 = meshComponent->uv[uvID2];
					vec2 uv3 = meshComponent->uv[uvID3];

					int geometrySize = worldGeometry.size();
					// push_back() is too slow for append operation
					// insert() too
					worldGeometry.resize(geometrySize + 16);
					worldGeometry[geometrySize    ] = vertex1.x;
					worldGeometry[geometrySize + 1] = vertex1.y;
					worldGeometry[geometrySize + 2] = vertex1.z;
					worldGeometry[geometrySize + 3] = 0;
					worldGeometry[geometrySize + 4] = vertex2.x;
					worldGeometry[geometrySize + 5] = vertex2.y;
					worldGeometry[geometrySize + 6] = vertex2.z;
					worldGeometry[geometrySize + 7] = uv1.x;
					worldGeometry[geometrySize + 8] = vertex3.x;
					worldGeometry[geometrySize + 9] = vertex3.y;
					worldGeometry[geometrySize + 10] = vertex3.z;
					worldGeometry[geometrySize + 11] = uv1.y;
					worldGeometry[geometrySize + 12] = uv2.x;
					worldGeometry[geometrySize + 13] = uv2.y;
					worldGeometry[geometrySize + 14] = uv3.x;
					worldGeometry[geometrySize + 15] = uv3.y;

				}

				int bbend = bbstart + meshComponent->elementVertex.size() * 0.33333333334;
				int bbsize = boundingBoxes.size();

				boundingBoxes.resize(bbsize + 8);

				boundingBoxes[bbsize] = meshComponent->maxX;
				boundingBoxes[bbsize + 1] = meshComponent->maxY;
				boundingBoxes[bbsize + 2] = meshComponent->maxZ;
				boundingBoxes[bbsize + 3] = float(bbstart);

				boundingBoxes[bbsize + 4] = meshComponent->minX;
				boundingBoxes[bbsize + 5] = meshComponent->minY;
				boundingBoxes[bbsize + 6] = meshComponent->minZ;
				boundingBoxes[bbsize + 7] = float(bbend);
				totalTriangles = bbend;
			}else
			if (LightComponent* lightComponent = dynamic_cast<LightComponent*>(component)) {
				vec3 vertex = lightComponent->position;
				vertex = vec3(vertex.x, vertex.z, vertex.y);
				vertex *= actorSize;
				vertex = actorRotation * vertex;
				vertex += actorPosition;
				

				int lightSize = lights.size();
				lights.resize(lightSize+8);
				lights[lightSize] = vertex.x;
				lights[lightSize + 1] = vertex.y;
				lights[lightSize + 2] = vertex.z;
				lights[lightSize + 3] = lightComponent->radius;
				lights[lightSize + 4] = lightComponent->color.x;
				lights[lightSize + 5] = lightComponent->color.y;
				lights[lightSize + 6] = lightComponent->color.z;
				lights[lightSize + 7] = lightComponent->color.w;
			}
		}
	}
}

std::vector<float>* World::GetWorldLights()
{
	return &lights;
}

std::vector<float>* World::GetWorldGeometry()
{
	return &worldGeometry;
}

std::vector<float>* World::GetBoundingBoxes()
{
	return &boundingBoxes;
}


void World::SerializeWorld(std::string path, std::string name)
{
	std::ofstream world("content/"+path +"/"+name+".wretto");
	world.clear();

	// Write variables
	for (auto actor : actors) {
		std::string className = actor->className;
		world << "[" << className << "]" << "\n";

		for (int i = 0; i < actor->variableRegistryNames.size();i++) {
			classType varClass = getClassTypeFromString(actor->variableRegistryClass[i]);

			switch (varClass) {
			case booleanC:
				world << "bool" << " "; break;
			case integer:
				world << "int" << " "; break;
			case floating:
				world << "float" << " "; break;
			//case stringData:
				//world << "string" << " "; break;
			case vector2:
				world << "vec2" << " "; break;
			case vector3:
				world << "vec3" << " "; break;
			case vector4:
				world << "vec4" << " "; break;
			}

			if (varClass!=noneVar) {
				world << actor->variableRegistryNames[i] << " = ";

				void* ptrActor = actor->variableRegistry[i];
				switch (varClass) {
				case booleanC:
				{bool* outDataInt = static_cast<bool*>(ptrActor); world << *outDataInt; break; }
				case integer:
				{int* outDataInt = static_cast<int*>(ptrActor); world << *outDataInt; break; }
				case floating:
				{float* outDataFloat = static_cast<float*>(ptrActor); world << *outDataFloat; break; }
				//case stringData:
				//{std::string* outDataString = static_cast<std::string*>(ptrActor); world << *outDataString; break; }
				case vector2:
				{vec2* outDataVec2 = static_cast<vec2*>(ptrActor); world << outDataVec2->x << "," << outDataVec2->y; break; }
				case vector3:
				{vec3* outDataVec3 = static_cast<vec3*>(ptrActor); world << outDataVec3->x << "," << outDataVec3->y << "," << outDataVec3->z; break; }
				case vector4:
				{vec4* outDataVec4 = static_cast<vec4*>(ptrActor); world << outDataVec4->x << "," << outDataVec4->y << "," << outDataVec4->z << "," << outDataVec4->w; break; }
				}
				world << ";\n";
			}
			
		};
		for (Component* component: actor->components) {
			std::string componentName = component->classClassName;
			componentName = componentName.erase(0, 6);
			componentName = componentName.erase(componentName.size() - 10, componentName.size() - 1);
			world << "[[" << componentName << "]]" << "\n";
			for (int i = 0; i < component->variableRegistryNames.size(); i++) {
				classType varClass = getClassTypeFromString(component->variableRegistryClass[i]);

				switch (varClass) {
				case booleanC:
					world << "bool" << " "; break;
				case integer:
					world << "int" << " "; break;
				case floating:
					world << "float" << " "; break;
				//case stringData:
					//world << "string" << " "; break;
				case vector2:
					world << "vec2" << " "; break;
				case vector3:
					world << "vec3" << " "; break;
				case vector4:
					world << "vec4" << " "; break;
				}

				if (varClass != noneVar) {
					world << component->variableRegistryNames[i] << " = ";

					void* ptrActor = component->variableRegistry[i];
					switch (varClass) {
					case booleanC:
					{bool* outDataInt = static_cast<bool*>(ptrActor); world << *outDataInt; break; }
					case integer:
					{int* outDataInt = static_cast<int*>(ptrActor); world << *outDataInt; break; }
					case floating:
					{float* outDataFloat = static_cast<float*>(ptrActor); world << *outDataFloat; break; }
					//case stringData:
					//{std::string* outDataString = static_cast<std::string*>(ptrActor); world << *outDataString; break; }
					case vector2:
					{vec2* outDataVec2 = static_cast<vec2*>(ptrActor); world << outDataVec2->x << "," << outDataVec2->y; break; }
					case vector3:
					{vec3* outDataVec3 = static_cast<vec3*>(ptrActor); world << outDataVec3->x << "," << outDataVec3->y << "," << outDataVec3->z; break; }
					case vector4:
					{vec4* outDataVec4 = static_cast<vec4*>(ptrActor); world << outDataVec4->x << "," << outDataVec4->y << "," << outDataVec4->z << "," << outDataVec4->w; break; }
					}
					world << ";\n";
				}

			};
		};
	}
	// Close the file
	world.close();
}
