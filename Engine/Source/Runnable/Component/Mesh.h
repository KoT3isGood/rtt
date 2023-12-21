#pragma once
#include "Component.h"
#include "Runtime/Engine/Tokenizer/Tokenizer.h"

class Mesh : public Component {
public:
	std::string lastFilePath;

	Mesh() = default;

	float maxX = -FLT_MAX;
	float minX = FLT_MAX;
	float maxY = -FLT_MAX;
	float minY = FLT_MAX;
	float maxZ = -FLT_MAX;
	float minZ = FLT_MAX;

	int totalMaterials = -1;
	//std::vector<Material> materials = {};
	std::vector<int> elementMaterial = {}; // 0,0,0,0,0,1,1,1 example:
	std::vector<int> elementVertex = {};
	std::vector<int> elementUv = {};
	std::vector<int> elementNormal = {};

	std::vector<vec3> vertex = {};
	std::vector<vec3> modifiedVertex = {};
	std::vector<vec2> uv = {};
	std::vector<vec3> normal = {};

	void loadFromFile(std::string filePath);
	void EventBegin() override;
	void EventEnd() override;
	void EventTick(float deltaTime) override;
};