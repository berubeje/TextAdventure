#include "InteractableManager.h"
#include "Door.h"
#include "Note.h"
#include "Enemy.h"
#include "Key.h"
#include "Weapon.h"
#include "Barrier.h"
#include <functional>
#include <map>


void InteractableManager::CreateInteractablesFromJSON(json::JSON& items, json::JSON& object)
{
	std::map < std::string, std::function<Obstacle* ()>> creationMap;

	creationMap.emplace("Door", std::function<Obstacle * ()>(Door::Create));
	creationMap.emplace("Enemy", std::function<Obstacle * ()>(Enemy::Create));
	creationMap.emplace("Barrier", std::function<Obstacle * ()>(Barrier::Create));
	creationMap.emplace("Note", std::function<Obstacle * ()>(Note::Create));
	creationMap.emplace("Key", std::function<Obstacle * ()>(Key::Create));
	creationMap.emplace("Weapon", std::function<Obstacle * ()>(Weapon::Create));


	for (auto obj : object.ArrayRange())
	{
		Obstacle* newObj = nullptr;

		newObj = creationMap[obj["ClassName"].ToString()]();
		newObj->Initialize(obj);
		AddInteractableObject(newObj);

	}

	for (auto item : items.ArrayRange())
	{
		Obstacle* newItem = nullptr;


		newItem = creationMap[item["ClassName"].ToString()]();
		newItem->Initialize(item);
		AddInteractableObject(newItem);


	}
}

void InteractableManager::AddInteractableObject(Obstacle* inter)
{
	interactables.push_back(inter);
}



std::string InteractableManager::GetInteractableDescriptions(int& id)
{
	std::string finalString = "";

	for (auto inter:interactables)
	{
		if (inter->GetLocation() == id)
		{
			finalString += inter->GetDescription() + "\n";
		}
	}

	return finalString;
}

std::list<Obstacle*> InteractableManager::GetInteractablesByLocationId(int& id)
{
	std::list<Obstacle*> newList;

	for (auto inter : interactables)
	{
		if (inter->GetLocation() == id)
		{
			newList.push_back(inter);
		}
	}
	return newList;
}

