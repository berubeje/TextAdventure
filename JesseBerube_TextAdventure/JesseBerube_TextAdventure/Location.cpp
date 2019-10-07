#include "Location.h"

Location::Location(int id, std::string name, std::string desc)
{
	locationID = id;
	locationName = name;
	description = desc;

}

Location::~Location()
{
	for (auto dir : directions)
	{
		delete dir;
	}
}

void Location::CreateDirectionsFromJSON(json::JSON& node)
{
	//json::JSON directionArray = node["Directions"];

	for (auto dir : node.ArrayRange())
	{
		Direction* newDir = new Direction(dir["Location Id"].ToInt(), dir["Direction"].ToString(), dir["Condition"].ToString(), dir["Condition Failure"].ToString());
		AddDirection(newDir);
	}
}

void Location::AddDirection(Direction* dir)
{

}
