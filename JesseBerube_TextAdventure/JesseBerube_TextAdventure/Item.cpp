#include "Item.h"

Item::Item(int loc, std::string name, std::string info)
	:Interactable(loc, name), worldInfo(info)
{
	validVerbs.push_back("USE");
	validVerbs.push_back("DROP");
	validVerbs.push_back("PICKUP");
}

Item::~Item()
{
}
