#pragma once
#include "json.hpp"
#include <list>

class Item;

class Player
{
private:
	int location;
	bool hasFriend;
	std::list<Item*> inventory;

public:
	inline static Player& Instance() {
		static Player instance;
		return instance;
	}

	void SetupPlayer(json::JSON& node);
	void ChangeLocation(int loc);
	void SetFriend(bool set);
	int& GetLocation() { return location; }
	void SetupInventory();
	void AddToInventory(Item* item);
	void RemoveFromInventory(Item* item);

private:
	inline explicit Player()
	{
	}

	inline ~Player()
	{
	}

	inline explicit Player(Player const&)
	{
	}

	inline Player& operator=(Player const&)
	{
		return *this;
	}
};

