#ifndef INCLUDED_MYLIGHTSYSTEM
#define INCLUDED_MYLIGHTSYSTEM

#include <LTBL\Light\LightSystem.h>
#include <LTBL\Light\Light_Point.h>
#include <LTBL\Utils.h>

class MyLightSystem
{
public:
	MyLightSystem();
	~MyLightSystem();

	static ltbl::LightSystem* getLightSystem();
	static void setLightSystem(ltbl::LightSystem*);

private:
	static ltbl::LightSystem* sLightSystem;
};

#endif