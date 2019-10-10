#include "Item.h"

Item::Item(int loc, std::string name, std::string info)
	:Interactable(loc, name), worldInfo(info)
{
}

Item::~Item()
{
}
