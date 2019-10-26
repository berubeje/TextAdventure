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
	for (auto dir : node.ArrayRange())
	{
		Direction* newDir = new Direction(dir["ToLocationId"].ToInt(), dir["CompassDirection"].ToString(), dir["ConditionFailure"].ToString());
		AddDirection(newDir);
	}
}

void Location::AddDirection(Direction* dir)
{
	directions.push_back(dir);
}

Direction* Location::GetDirection(std::string dir)
{
	for (auto direct : directions)
	{
		if (direct->GetDirection() == dir)
		{
			return direct;
		}
	}

	return nullptr;
}
	