#include "rttmath.h"

mat3x3 rotationToMat3x3(vec3 rotation)
{
	float cx = glm::cos(rotation.x);
	float sx = glm::sin(rotation.x);
	float cy = glm::cos(rotation.y);
	float sy = glm::sin(rotation.y);
	float cz = glm::cos(rotation.z);
	float sz = glm::sin(rotation.z);

	return mat3x3(
		cx, 0, sx,
		0, 1, 0,
		-sx, 0, cx
	) * mat3x3(
		1, 0, 0,
		0, cy, -sy,
		0, sy, cy
	) * mat3x3(
		cz, -sz, 0,
		sz, cz, 0,
		0, 0, 1
	);
}
