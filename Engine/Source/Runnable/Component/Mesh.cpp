#include "Mesh.h"

void Mesh::loadFromFile(std::string filePath)
{
	lastFilePath = filePath;
	Tokenizer tokens = Tokenizer(filePath, { "\n"," ","/" }, false);
	int fcounter = 0;
	vertex = {};
	normal = {};
	uv = {};
	//materials = {};
	elementVertex = {};
	elementNormal = {};
	elementUv = {};
	elementMaterial = {};
	for (int i = 0; i < tokens.tokens.size(); i++) {

		if (tokens.tokens[i] == "v") {
			float vertex1 = stof(tokens.tokens[i + 1]);
			float vertex2 = stof(tokens.tokens[i + 2]);
			float vertex3 = stof(tokens.tokens[i + 3]);
			vec3 newVertex = vec3(vertex1, vertex2, vertex3);
			vertex.push_back(newVertex);



			i += 3;

		}
		if (tokens.tokens[i] == "vn") {
			float vertex1 = stof(tokens.tokens[i + 1]);
			float vertex2 = stof(tokens.tokens[i + 2]);
			float vertex3 = stof(tokens.tokens[i + 3]);
			vec3 newVertex = vec3(vertex1, vertex2, vertex3);
			normal.push_back(newVertex);
			i += 3;
		}

		if (tokens.tokens[i] == "vt") {
			float vertex1 = stof(tokens.tokens[i + 1]);
			float vertex2 = stof(tokens.tokens[i + 2]);
			vec2 newVertex = vec2(vertex1, vertex2);
			uv.push_back(newVertex);
			i += 2;
		}

		if (tokens.tokens[i] == "usemtl") {
			totalMaterials++;
		}

		if (tokens.tokens[i] == "f") {

			fcounter++;
			int v1 = stoi(tokens.tokens[i + 1]);
			int vt1 = stoi(tokens.tokens[i + 2]);
			int vn1 = stoi(tokens.tokens[i + 3]);
			int v2 = stoi(tokens.tokens[i + 4]);
			int vt2 = stoi(tokens.tokens[i + 5]);
			int vn2 = stoi(tokens.tokens[i + 6]);
			int v3 = stoi(tokens.tokens[i + 7]);
			int vt3 = stoi(tokens.tokens[i + 8]);
			int vn3 = stoi(tokens.tokens[i + 9]);

			// TODO: replace 
			elementVertex.push_back(v1);
			elementVertex.push_back(v2);
			elementVertex.push_back(v3);

			elementUv.push_back(vt1);
			elementUv.push_back(vt2);
			elementUv.push_back(vt3);

			elementNormal.push_back(vn1);
			elementNormal.push_back(vn2);
			elementNormal.push_back(vn3);
			if (totalMaterials != -1) {
				elementMaterial.push_back(totalMaterials);
			}
			else {
				totalMaterials = 0;
				//materials.push_back(Material());
				elementMaterial.push_back(0);
			}



			i += 9;
		}
	};
}

void Mesh::EventBegin()
{
}

void Mesh::EventEnd()
{
}

void Mesh::EventTick(float deltaTime)
{
}
