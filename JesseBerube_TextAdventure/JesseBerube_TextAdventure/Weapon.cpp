#include "Weapon.h"

//Weapon::Weapon(int loc, std::string name, std::string noun, std::string info)
//	:Item(loc,name,noun,info)
//{
//}

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::UseItem()
{
}

void Weapon::Initialize(json::JSON& node)
{
	//Obstacle
	interactableName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();


	//Item
	worldInfo = node["WorldInfo"].ToString();
}
