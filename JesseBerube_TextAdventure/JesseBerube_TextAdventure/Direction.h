#pragma once
#include <string>
class Direction
{
private:
	int locationID;
	std::string direction;
	std::string failureDescription;

public:
	Direction(int id, std::string dir, std::string desc);
	~Direction();
	std::string& GetDirection() { return direction; }
	int& GetToLocation() { return locationID; }
	std::string& GetFailure() { return failureDescription; }

};

