#pragma once
#include "json.hpp"
class Player
{
private:
	int location;
	bool hasFriend;
public:
	Player();
	~Player();
	void SetupPlayer(json::JSON& node);
	void ChangeLocation(int loc);
	void SetFriend(bool set);
};

