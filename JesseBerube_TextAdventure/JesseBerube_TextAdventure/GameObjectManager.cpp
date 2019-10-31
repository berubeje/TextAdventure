#include "GameObjectManager.h"
#include "Door.h"
#include "Note.h"
#include "Enemy.h"
#include "Key.h"
#include "Weapon.h"
#include "Barrier.h"
#include "Obstacle.h"
#include "Player.h"
#include <functional>
#include <map>


GameObjectManager::GameObjectManager()
{
	player = new Player();
	friendLocation = new Friend();
}


GameObjectManager::~GameObjectManager()
{
	for (auto ob : obstacleVector)
	{
		delete ob;
	}

	for (auto it : itemVector)
	{
		delete it;
	}

	for (auto enemy : enemyVector)
	{
		delete enemy;
	}

	delete player;
	delete friendLocation;
}

void GameObjectManager::CreateInteractablesFromJSON(json::JSON& items, json::JSON& obstacle, json::JSON& enemies)
{
	//Using function pointers to load in items and obstacles
	std::map < std::string, std::function<Obstacle* ()>> obstacleMap;
	std::map < std::string, std::function<Item* ()>> itemMap;

	obstacleMap.emplace("Door", std::function<Obstacle * ()>(Door::Create));
	obstacleMap.emplace("Barrier", std::function<Obstacle * ()>(Barrier::Create));
	
	itemMap.emplace("Note", std::function<Item * ()>(Note::Create));
	itemMap.emplace("Key", std::function<Item * ()>(Key::Create));
	itemMap.emplace("Weapon", std::function<Item * ()>(Weapon::Create));


	for (auto ob : obstacle.ArrayRange())
	{
		Obstacle* newObstacle = nullptr;

		newObstacle = obstacleMap[ob["ClassName"].ToString()]();
		newObstacle->Initialize(ob);
		AddObstacle(newObstacle);

	}

	for (auto item : items.ArrayRange())
	{
		Item* newItem = nullptr;

		newItem = itemMap[item["ClassName"].ToString()]();
		newItem->Initialize(item);
		AddItem(newItem);


	}

	for (auto enemy : enemies.ArrayRange())
	{
		Enemy* newEnemy = new Enemy();
		newEnemy->Initialize(enemy);
		AddEnemy(newEnemy);

	}
}

void GameObjectManager::CreatePlayerAndFriendFromJSON(json::JSON& playerJSON, json::JSON& friendJSON)
{
	player->SetupPlayer(playerJSON);
	player->SetupInventory();
	friendLocation->SetFriendLocation(friendJSON["FriendLocation"].ToInt());
}


void GameObjectManager::AddObstacle(Obstacle* _obstacle)
{
	obstacleVector.push_back(_obstacle);
}

void GameObjectManager::AddItem(Item* _item)
{
	itemVector.push_back(_item);
}
void GameObjectManager::AddEnemy(Enemy* _enemy)
{
	enemyVector.push_back(_enemy);
}



std::string GameObjectManager::GetInteractableDescriptions(int& id)
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

std::list<Obstacle*> GameObjectManager::GetObstaclesByLocationId(int& id)
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

std::list<Item*> GameObjectManager::GetItemsByLocationId(int& id)
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

std::list<Enemy*> GameObjectManager::GetEnemiesByLocationId(int& id)
{
	std::list<Enemy*> newList;

	for (auto enemy : enemyVector)
	{
		if (enemy->GetLocation() == id)
		{
			newList.push_back(enemy);
		}
	}
	return newList;
}

