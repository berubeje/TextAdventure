#pragma once
#include <vector>
#include "Obstacle.h"
#include "Item.h"
#include "json.hpp"
#include <list>
class ObstacleAndItemManager
{
private:
	std::vector<Obstacle*> obstacleVector;
	std::vector<Item*> itemVector;


public:

	inline static ObstacleAndItemManager& Instance() {
		static ObstacleAndItemManager instance;
		return instance;
	}


    void CreateInteractablesFromJSON(json::JSON& items, json::JSON& other);
	void AddObstacle(Obstacle* _obstacle);
	void AddItem(Item* _item);
	std::vector<Obstacle*>* GetObstacleArray() { return &obstacleVector; };
	std::vector<Item*>* GetItemArray() { return &itemVector; };
	std::string GetInteractableDescriptions(int& id);

	std::list<Obstacle*> GetObstaclesByLocationId(int& id);
	std::list<Item*> GetItemsByLocationId(int& id);

	void Initialize() {};

private:
	inline explicit ObstacleAndItemManager()
	{
	}

	inline ~ObstacleAndItemManager()
	{
		for (auto ob : obstacleVector)
		{
			delete ob;
		}

		for (auto it : itemVector)
		{
			delete it;
		}
	}

	inline explicit ObstacleAndItemManager(ObstacleAndItemManager const&)
	{
	}

	inline ObstacleAndItemManager& operator=(ObstacleAndItemManager const&)
	{
		return *this;
	}
};

