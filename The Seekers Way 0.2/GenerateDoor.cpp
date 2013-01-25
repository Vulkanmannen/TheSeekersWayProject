#include "GenerateDoor.h"


GenerateDoor::GenerateDoor()
	{}


GenerateDoor::~GenerateDoor()
	{}

void GenerateDoors(TiXmlDocument &document)
{
	TiXmlElement* root = document.FirstChildElement("Body");
	root = root->FirstChildElement("Door");
	
	while(root)
	{
			
	}
}