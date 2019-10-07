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
		Direction* newDir = new Direction(dir["Location Id"].ToInt(), dir["Direction"].ToString(), dir["Condition"].ToString(), dir["Condition Failure"].ToString());
		AddDirection(newDir);
	}
}

void Location::CreateObjectsFromJSON(json::JSON& node)
{
	for (auto obj:node.ArrayRange())
	{
		Object* newObj = new Object(obj["Object"].ToString(), obj["State"].ToBool(), obj["If True"].ToString(), obj["If False"].ToString());
		AddObject(newObj);
	}
}

void Location::AddDirection(Direction* dir)
{
	directions.push_back(dir);
}

void Location::AddObject(Object* obj)
{
	objects.push_back(obj);
}
