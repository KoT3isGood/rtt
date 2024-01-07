#pragma once
#include "..\Component.h"

class LightComponent : public Component { REFLECTCOMPONENT();
public:
	LightComponent();
	float radius = 1.0;
	vec4 color = vec4(1.0);
};