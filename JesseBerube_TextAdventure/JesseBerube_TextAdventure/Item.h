#pragma once
#include <string>
#include "Interactable.h"

class Item: public Interactable
{
protected:
	std::string worldInfo;

public:
	Item(int loc, std::string name, std::string info);
	virtual ~Item();
	//a location id of 0 is considered the player
	virtual void Pickup() { locationId = 0; };
	virtual void Drop(int location) { locationId = location; };
	virtual void UseItem() = 0;
};

