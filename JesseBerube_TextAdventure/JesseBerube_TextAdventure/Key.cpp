#include "Key.h"
#include "Enemy.h"
#include "Obstacle.h"

#include <iostream>
#include "DatabaseManager.h"

Key::Key()
{
}

Key::~Key()
{
}

void Key::UseItem(std::string verb)
{
	if (verb == "USE")
	{
		std::cout << "*Use " + itemName + " on what?*\n" << std::endl;
	}
	else
	{
		std::cout << "*You cannot use the " + itemName + " this way.*\n" << std::endl;
	}
}

void Key::UseItem(std::string verb, Enemy* enemy)
{
	if (verb == "USE")
	{
		//Key items dont have a use on enemies in this version of the game, but they could in the future
		std::cout << "*You cannot use the " + itemName + " this way.*\n" << std::endl;
	}
	else
	{
		std::cout << "*You cannot use the " + itemName + " this way.*\n" << std::endl;
	}
}

void Key::UseItem(std::string verb, Obstacle* obstacle)
{
	if (verb == "USE")
	{
		if (obstacle->GetName() == doorBarrierName)
		{
			obstacle->Resolve();

			//Takes item out of them game world
			locationId = -1;
			DatabaseManager::Instance().IncrementActions();
		}
	}
	else
	{
		std::cout << "*You cannot use the " + itemName + " this way.*\n" << std::endl;
	}
}

void Key::Initialize(json::JSON& node)
{
	//Item
	itemName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();
	worldInfo = node["WorldInfo"].ToString();

	//Note
	doorBarrierName = node["DoorBarrierName"].ToString();
}

