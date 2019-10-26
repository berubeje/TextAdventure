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
	virtual void UseItem();

	virtual void Initialize(json::JSON& node);

	static Item* Create() { return new Key(); }
};

