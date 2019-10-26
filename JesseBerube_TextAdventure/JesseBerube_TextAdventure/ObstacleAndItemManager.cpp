#include "ObstacleAndItemManager.h"
#include "Door.h"
#include "Note.h"
#include "Enemy.h"
#include "Key.h"
#include "Weapon.h"
#include "Barrier.h"
#include "Obstacle.h"
#include <functional>
#include <map>



void ObstacleAndItemManager::CreateInteractablesFromJSON(json::JSON& items, json::JSON& object)
{
	std::map < std::string, std::function<Obstacle* ()>> obstacleMap;
	std::map < std::string, std::function<Item* ()>> itemMap;

	obstacleMap.emplace("Door", std::function<Obstacle * ()>(Door::Create));
	obstacleMap.emplace("Enemy", std::function<Obstacle * ()>(Enemy::Create));
	obstacleMap.emplace("Barrier", std::function<Obstacle * ()>(Barrier::Create));
	itemMap.emplace("Note", std::function<Item * ()>(Note::Create));
	itemMap.emplace("Key", std::function<Item * ()>(Key::Create));
	itemMap.emplace("Weapon", std::function<Item * ()>(Weapon::Create));


	for (auto obj : object.ArrayRange())
	{
		Obstacle* newObstacle = nullptr;

		newObstacle = obstacleMap[obj["ClassName"].ToString()]();
		newObstacle->Initialize(obj);
		AddObstacle(newObstacle);

	}

	for (auto item : items.ArrayRange())
	{
		Item* newItem = nullptr;

		newItem = itemMap[item["ClassName"].ToString()]();
		newItem->Initialize(item);
		AddItem(newItem);


	}
}


void ObstacleAndItemManager::AddObstacle(Obstacle* _obstacle)
{
	obstacleVector.push_back(_obstacle);
}

void ObstacleAndItemManager::AddItem(Item* _item)
{
	itemVector.push_back(_item);
}



std::string ObstacleAndItemManager::GetInteractableDescriptions(int& id)
{
	std::string finalString = "";

	for (auto ob: obstacleVector)
	{
		if (ob->GetLocation() == id)
		{
			finalString += ob->GetDescription() + "\n";
		}
	}

	for (auto it : itemVector)
	{
		if (it->GetLocation() == id)
		{
			finalString += it->GetDescription() + "\n";
		}
	}

	return finalString;
}

std::list<Obstacle*> ObstacleAndItemManager::GetObstaclesByLocationId(int& id)
{
	std::list<Obstacle*> newList;

	for (auto ob : obstacleVector)
	{
		if (ob->GetLocation() == id)
		{
			newList.push_back(ob);
		}
	}
	return newList;
}

std::list<Item*> ObstacleAndItemManager::GetItemsByLocationId(int& id)
{
	std::list<Item*> newList;

	for (auto it : itemVector)
	{
		if (it->GetLocation() == id)
		{
			newList.push_back(it);
		}
	}
	return newList;
}

