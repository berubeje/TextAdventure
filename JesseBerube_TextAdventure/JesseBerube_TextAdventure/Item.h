#pragma once
#include <string>
#include "Interactable.h"

class Item: public Interactable
{
private:


public:
	Item();
	virtual ~Item();
	virtual void AddVerb();
	virtual int  GetLocation() { return locationId; };
	virtual void Pickup() { locationId = 0; };
	virtual void Drop(int location) { locationId = location; };
	virtual void UseItem() = 0;
};

