#pragma once
#include "Item.h"

class Enemy;
class Obstacle;

class Weapon :
	public Item
{

public:
	Weapon();
	//Weapon(int loc, std::string name, std::string noun, std::string info);
	virtual ~Weapon();
	virtual void UseItem(std::string verb);
	virtual void UseItem(std::string verb, Enemy* enemy);
	virtual void UseItem(std::string verb, Obstacle* obstacle);
	
	virtual void Initialize(json::JSON& node);

	static Item* Create() { return new Weapon(); }
};

