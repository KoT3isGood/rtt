#include "CurrentProperties.h"

World currentWorld = World();

World* GetWorld()
{
	return &currentWorld;
}
