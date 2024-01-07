#pragma once
#include "Component.h"

class CameraComponent : public Component {
	REFLECTCOMPONENT();
public:
	CameraComponent();
	bool isOrtoGraphic = false; 
	float orthoSize = 1;
};