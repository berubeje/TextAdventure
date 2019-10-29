#pragma once
#include <string>
#include <vector>
#include "json.hpp"

class Enemy;
class Obstacle;

class Item
{
protected:
	int locationId;
	std::string classType;
	std::vector<std::string> validVerbs;
	std::string commandNoun;
	std::string itemName;
	std::string worldInfo;

public:
	Item();
	//Item(int loc, std::string name, std::string noun, std::string info);
	virtual ~Item();
	//a location id of 0 is considered the player

	const int& GetLocation() { return locationId; }
	const std::string& GetType() { return classType; }
    std::vector<std::string>* GetValidVerbs() { return &validVerbs; }
	const std::string& GetCommandName() { return commandNoun; }
	const std::string& GetName() { return itemName; }
	void SetLocation(int set) { locationId = set; }

	virtual std::string GetDescription() { return worldInfo + " : " + commandNoun; }

	virtual void UseItem(std::string verb) = 0;
	virtual void UseItem(std::string verb, Enemy* enemy) = 0;
	virtual void UseItem(std::string verb, Obstacle* obstacle) = 0;
	virtual void Initialize(json::JSON&) = 0;
};

