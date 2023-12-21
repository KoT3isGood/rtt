#include "World.h"

World::World(std::string worldName)
{
}

void World::SpawnActor(Actor* actor)
{
	actors.push_back(actor);
}

void World::UpdateWorld(float deltaTime)
{
	for (Actor* actor : actors) {
		actor->EventTick(deltaTime);
	};
}

void World::PrecalculateTriangles()
{
	worldGeometry = {};
	boundingBoxes = {};
	int totalTriangles = 0;
	for (auto actor : actors) {
		mat3x3 actorRotation = rotationToMat3x3(actor->rotation);
		vec3 actorPosition = actor->position;
		vec3 actorSize = actor->size;
		for (auto component : actor->components) {
			mat3x3 componentRotation = rotationToMat3x3(component->rotation);
			vec3 componentPosition = component->position;
			vec3 componentSize = component->size;
			Mesh* thisComponent = dynamic_cast<Mesh*>(component);
			thisComponent->modifiedVertex = thisComponent->vertex;

			int bbstart = totalTriangles;

			// apply transform
			for (int i = 0; i < thisComponent->modifiedVertex.size();i++) {
				vec3* vertex = &thisComponent->modifiedVertex[i];
				// Iteration 1: component transform
				//*vertex *= componentSize;
				*vertex = componentRotation * *vertex;
				*vertex += componentPosition;
				// Iteration 1: actor transform
				//*vertex *= actorSize;
				*vertex = actorRotation * *vertex;
				*vertex += actorPosition;

				// Calculate bounding boxes;
				if (vertex->x > thisComponent->maxX)
				{
					thisComponent->maxX = vertex->x;
				}
				if (vertex->x < thisComponent->minX)
				{
					thisComponent->minX = vertex->x;
				}
				//y
				if (vertex->y > thisComponent->maxY)
				{
					thisComponent->maxY = vertex->y;
				}
				if (vertex->y < thisComponent->minY)
				{
					thisComponent->minY = vertex->y;
				}
				//z
				if (vertex->z > thisComponent->maxZ)
				{
					thisComponent->maxZ = vertex->z;
				}
				if (vertex->z < thisComponent->minZ)
				{
					thisComponent->minZ = vertex->z;
				}
			}
			// generate world triangle matrix
			for (int i = 0; i < thisComponent->elementVertex.size(); i+=3) {
				int vertexID1 = thisComponent->elementVertex[i] - 1;
				int vertexID2 = thisComponent->elementVertex[i + 1] - 1;
				int vertexID3 = thisComponent->elementVertex[i + 2] - 1;
				vec3 vertex1 = thisComponent->modifiedVertex[vertexID1];
				vec3 vertex2 = thisComponent->modifiedVertex[vertexID2];
				vec3 vertex3 = thisComponent->modifiedVertex[vertexID3];

				int uvID1 = thisComponent->elementUv[i] - 1;
				int uvID2 = thisComponent->elementUv[i + 1] - 1;
				int uvID3 = thisComponent->elementUv[i + 2] - 1;
				vec2 uv1 = thisComponent->uv[uvID1];
				vec2 uv2 = thisComponent->uv[uvID2];
				vec2 uv3 = thisComponent->uv[uvID3];

				int geometrySize = worldGeometry.size();
				// push_back() is too slow for append operation
				// insert() too
				worldGeometry.resize(geometrySize + 16);
				worldGeometry[geometrySize + 0] = vertex1.x;
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
			
			int bbend = bbstart + thisComponent->elementVertex.size() * 0.33333333334;
			int bbsize = boundingBoxes.size();

			boundingBoxes.resize(bbsize+8);

			boundingBoxes[bbsize] = thisComponent->maxX;
			boundingBoxes[bbsize+1] = thisComponent->maxY;
			boundingBoxes[bbsize+2] = thisComponent->maxZ;
			boundingBoxes[bbsize+3] = float(bbstart);

			boundingBoxes[bbsize+4] = thisComponent->minX;
			boundingBoxes[bbsize + 5] = thisComponent->minY;
			boundingBoxes[bbsize + 6] = thisComponent->minZ;
			boundingBoxes[bbsize + 7] = float(bbend);
			totalTriangles = bbend;
		}
	}
}

std::vector<float>* World::GetWorldGeometry()
{
	return &worldGeometry;
}

std::vector<float>* World::GetBoundingBoxes()
{
	return &boundingBoxes;
}
