#include "Direction.h"

Direction::Direction(int id, std::string dir, std::string cond, std::string desc)
{
	locationID = id;
	direction = dir;
	failureDescription = desc;
	condition = cond;
}

Direction::~Direction()
{
}
