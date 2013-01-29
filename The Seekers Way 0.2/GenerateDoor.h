#ifndef INCLUDED_GENERATEDOOR
#define INCLUDED_GENERATEDOOR

#include "tinyxml.h"
#include <string>

class GenerateDoor
{
public:
	GenerateDoor();
	~GenerateDoor();

	static void GenerateDoors();

	static void loadDocument(std::string s);
private:
	static TiXmlDocument sDocument;
};

#endif