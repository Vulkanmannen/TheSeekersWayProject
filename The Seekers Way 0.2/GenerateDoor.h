#ifndef INCLUDED_GENERATEDOOR
#define INCLUDED_GENERATEDOOR

#include "tinyxml.h"

class GenerateDoor
{
public:
	GenerateDoor();
	~GenerateDoor();

	static void GenerateDoors(TiXmlDocument &document);
};

#endif