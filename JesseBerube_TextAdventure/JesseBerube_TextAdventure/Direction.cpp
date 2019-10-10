#include "Direction.h"

Direction::Direction(int id, std::string dir, std::string desc)
{
	locationID = id;
	direction = dir;
	failureDescription = desc;
}

Direction::~Direction()
{
}
