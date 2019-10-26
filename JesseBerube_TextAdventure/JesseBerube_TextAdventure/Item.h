#pragma once
#include <string>
#include <vector>
#include "json.hpp"


class Item
{
protected:
	int locationId;
	std::string classType;
	std::vector<std::string> validVerbs;
	std::string commandNoun;
	std::string interactableName;
	std::string worldInfo;

public:
	Item();
	//Item(int loc, std::string name, std::string noun, std::string info);
	virtual ~Item();
	//a location id of 0 is considered the player

	const virtual int& GetLocation() { return locationId; }
	const virtual std::string& GetType() { return classType; }
	virtual std::vector<std::string>* GetValidVerbs() { return &validVerbs; }
	const virtual std::string& GetCommandName() { return commandNoun; }

	virtual void Pickup() { locationId = 0; };
	virtual void Drop(int location) { locationId = location; };
	virtual std::string GetDescription() { return worldInfo; }

	virtual void UseItem() = 0;
	virtual void Initialize(json::JSON&) = 0;
};

