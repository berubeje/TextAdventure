#pragma once
#include "json.hpp"
#include <list>

class Item;

class Player
{
private:
	int location;
	bool hasFriend;
	bool isDead;
	std::list<Item*> inventory;

public:
	Player();
	~Player();

	bool& GetFriend() { return hasFriend; }
	bool& GetDead() { return isDead; }
    int& GetLocation() { return location; }

	void SetupPlayer(json::JSON& node);
	void ChangeLocation(int loc);
	void SetFriend(bool set);
	void SetupInventory();
	
	void AddToInventory(Item* item) { inventory.push_back(item); }
	void RemoveFromInventory(Item* item) { inventory.remove(item); }
	std::list<Item*>& GetInventory() { return inventory; }
	void Die();
	
	void SetDead(bool set) { isDead = set; }

};

