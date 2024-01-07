#include "CameraComponent.h"

void CameraComponent::RegisterVariables()
{
	variableRegistryNames = {};
	variableRegistry = {};
	variableRegistryClass = {};
	classClassName = typeid(this).name();
	className = "CameraComponent";
	Register(position);
	Register(rotation);
	Register(isOrtoGraphic);
	Register(orthoSize);
}

CameraComponent::CameraComponent()
{

}
