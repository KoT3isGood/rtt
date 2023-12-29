#include "LightComponent.h"
LightComponent::LightComponent()
{
	//RegisterVariables();
}
void LightComponent::RegisterVariables() {
	variableRegistryNames = {};
	variableRegistry = {};
	variableRegistryClass = {};
	classClassName = typeid(this).name();
	className = "LightComponent";
	Register(position);
	Register(radius);
	Register(color);
}