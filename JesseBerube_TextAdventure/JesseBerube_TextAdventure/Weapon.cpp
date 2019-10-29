#include "Weapon.h"
#include "Enemy.h"
#include "Obstacle.h"

//Weapon::Weapon(int loc, std::string name, std::string noun, std::string info)
//	:Item(loc,name,noun,info)
//{
//}

Weapon::Weapon()
{
	validVerbs.push_back("ATTACK");
}

Weapon::~Weapon()
{
}

void Weapon::UseItem(std::string verb)
{
	if (verb == "ATTACK")
	{
		std::cout << "*Attack what?*\n" << std::endl;
	}
	else
	{
		std::cout << "*Weapons are for ATTACKing*\n" << std::endl;
	}
}

void Weapon::UseItem(std::string verb, Enemy* enemy)
{
	if (verb == "ATTACK")
	{
		enemy->KillEnemy();
	}
	else
	{
		std::cout << "*Weapons are for ATTACKing*\n" << std::endl;
	}
}

void Weapon::UseItem(std::string verb, Obstacle* obstacle)
{
	//Does not really have a use for obstacles in this game right now, but could be used in the future such as breaking down a door with a weapon
	if (verb == "ATTACK")
	{
		std::cout << "*You cannot use your weapon like that*\n" << std::endl;
	}
	else
	{
		std::cout << "*Weapons are for ATTACKing*\n" << std::endl;
	}
}

void Weapon::Initialize(json::JSON& node)
{
	//Item
	itemName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();
	worldInfo = node["WorldInfo"].ToString();
}
