#pragma once
class Friend
{
private:
	 int friendLocation;

public:
	Friend();
	~Friend();
	void SetFriendLocation(int loc) { friendLocation = loc; }
	int& GetFriendLocation() { return friendLocation; }
};

