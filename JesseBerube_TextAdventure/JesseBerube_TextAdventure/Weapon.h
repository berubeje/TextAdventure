#pragma once
#include "Item.h"
class Weapon :
	public Item
{

public:
	Weapon();
	//Weapon(int loc, std::string name, std::string noun, std::string info);
	virtual ~Weapon();
	virtual void UseItem();
	
	virtual void Initialize(json::JSON& node);

	static Item* Create() { return new Weapon(); }
};

