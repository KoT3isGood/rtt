#pragma once
#include "..\Component\CameraComponent.h"
#include "..\Actor\Actor.h"
class PlayerController {
public:
	Actor* ownedActor = nullptr;
};