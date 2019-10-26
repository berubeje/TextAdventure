#pragma once
class Friend
{
private:
	static int friendLocation;

public:
	static void SetFriendLocation(int loc) { friendLocation = loc; }
	static int& GetFriendLocaion() { return friendLocation; }
};

