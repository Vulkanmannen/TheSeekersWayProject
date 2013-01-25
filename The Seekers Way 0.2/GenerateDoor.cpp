#include "GenerateDoor.h"

TiXmlDocument GenerateDoor::sDocument;

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

void GenerateDoor::loadDocument(std::string &s)
{

}