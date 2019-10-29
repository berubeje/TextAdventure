#pragma once
#include "Obstacle.h"
#include "Item.h"
#include "Enemy.h"
#include "json.hpp"
#include "Friend.h"
#include "Player.h"
#include <list>
#include <vector>



class GameObjectManager
{
private:
	std::vector<Obstacle*> obstacleVector;
	std::vector<Item*> itemVector;
	std::vector<Enemy*> enemyVector;
	Player* player;
	Friend* friendLocation;

public:

	inline static GameObjectManager& Instance() {
		static GameObjectManager instance;
		return instance;
	}


    void CreateInteractablesFromJSON(json::JSON& items, json::JSON& obstacle, json::JSON& enemies);
	void CreatePlayerAndFriendFromJSON(json::JSON& playerJSON, json::JSON& friendJSON);
	void AddObstacle(Obstacle* _obstacle);
	void AddItem(Item* _item);

	void AddEnemy(Enemy* _enemy);
	
	std::vector<Obstacle*>& GetObstacleArray() { return obstacleVector; };
	std::vector<Item*>& GetItemArray() { return itemVector; };
	std::vector<Enemy*>& GetEnemyArray() { return enemyVector; };
	
	std::string GetInteractableDescriptions(int& id);

	std::list<Obstacle*> GetObstaclesByLocationId(int& id);
	std::list<Item*> GetItemsByLocationId(int& id);
	std::list<Enemy*> GetEnemiesByLocationId(int& id);

	Player* GetPlayer() { return player; }
	Friend* GetFriend() { return friendLocation; }

	void Initialize() {};

private:
	inline explicit GameObjectManager()
	{
		player = new Player();
		friendLocation = new Friend();
	}

	inline ~GameObjectManager()
	{
		for (auto ob : obstacleVector)
		{
			delete ob;
		}

		for (auto it : itemVector)
		{
			delete it;
		}

		delete player;
		delete friendLocation;
	}

	inline explicit GameObjectManager(GameObjectManager const&)
	{
	}

	inline GameObjectManager& operator=(GameObjectManager const&)
	{
		return *this;
	}
};

