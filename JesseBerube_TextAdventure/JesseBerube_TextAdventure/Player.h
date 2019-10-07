#pragma once
class Player
{
private:
	int location;
	bool hasFriend;
public:
	void ChangeLocation(int loc);
	void SetFriend(bool set);
};

