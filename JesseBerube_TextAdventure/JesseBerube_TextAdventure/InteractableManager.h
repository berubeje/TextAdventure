#pragma once
#include <vector>
#include "Interactable.h"
#include "json.hpp"
class InteractableManager
{
private:
	std::vector<Interactable*> interactables;

public:
	InteractableManager();
	~InteractableManager();
	void CreateInteractablesFromJSON(json::JSON& items, json::JSON& other);
	void AddInteractableObject(Interactable*);
};

