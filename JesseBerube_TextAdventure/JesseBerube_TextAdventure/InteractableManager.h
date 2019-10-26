#pragma once
#include <vector>
#include "Obstacle.h"
#include "json.hpp"
#include <list>
class InteractableManager
{
private:
	std::vector<Obstacle*> obstacles;
	std::vector<Item*> items;


public:

	inline static InteractableManager& Instance() {
		static InteractableManager instance;
		return instance;
	}


    void CreateInteractablesFromJSON(json::JSON& items, json::JSON& other);
	void AddInteractableObject(Obstacle*);
	std::vector<Obstacle*>* GetObstacleArray() { return &obstacles; };
	std::vector<Item*>* GetItemArray() { return &items; };
	std::string GetInteractableDescriptions(int& id);

	std::list<Obstacle*> GetObstaclesByLocationId(int& id);
	std::list<Item*> GetItemsByLocationId(int& id);

	void Initialize() {};

private:
	inline explicit InteractableManager()
	{
	}

	inline ~InteractableManager()
	{
		for (auto inter : interactables)
		{
			delete inter;
		}
	}

	inline explicit InteractableManager(InteractableManager const&)
	{
	}

	inline InteractableManager& operator=(InteractableManager const&)
	{
		return *this;
	}
};

