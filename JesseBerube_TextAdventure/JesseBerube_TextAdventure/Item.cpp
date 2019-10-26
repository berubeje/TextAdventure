#include "Item.h"


Item::Item()
{
	validVerbs.push_back("USE");
	validVerbs.push_back("DROP");
	validVerbs.push_back("PICKUP");
}

//Item::Item(int loc, std::string name, std::string noun ,std::string info)
//	:Obstacle(loc, name , noun), worldInfo(info)
//{

//}

Item::~Item()
{
}


