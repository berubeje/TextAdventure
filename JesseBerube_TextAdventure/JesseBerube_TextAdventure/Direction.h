#pragma once
#include <string>
class Direction
{
private:
	int locationID;
	std::string direction;
	std::string condition;
	std::string failureDescription;

public:
	Direction(int id, std::string dir, std::string cond, std::string desc);
	~Direction();


};

