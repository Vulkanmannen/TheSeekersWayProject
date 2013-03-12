#include "MyLightSystem.h"

ltbl::LightSystem* MyLightSystem::sLightSystem = NULL;

MyLightSystem::MyLightSystem()
	{}


MyLightSystem::~MyLightSystem()
	{}

ltbl::LightSystem* MyLightSystem::getLightSystem()
{
	return sLightSystem;
}

void MyLightSystem::setLightSystem(ltbl::LightSystem* lightSystem)
{
	 sLightSystem = lightSystem;
}