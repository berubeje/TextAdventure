#pragma once
#include "Item.h"
class Key :
	public Item
{
private:
	std::string doorBarrierName;

public:
	Key();
	virtual ~Key();
	virtual void UseItem(std::string verb);
	virtual void UseItem(std::string verb, Enemy* enemy);
	virtual void UseItem(std::string verb, Obstacle* obstacle);

	virtual void Initialize(json::JSON& node);

	static Item* Create() { return new Key(); }
};

