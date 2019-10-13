#include "LocationManager.h"
#include "Location.h"

LocationManager::LocationManager()
{
}

LocationManager::~LocationManager()
{
	for (auto loc:locations)
	{
		delete loc;
	}
}

void LocationManager::CreateLocationsFromJSON(json::JSON& node)
{
	for (auto loc:node.ArrayRange())
	{
		Location* newLoc = new Location(loc["Location Id"].ToInt(), loc["Location Name"].ToString(),loc["Description"].ToString());
	
		newLoc->CreateDirectionsFromJSON(loc["Directions"]);

		AddLocation(newLoc);

	}
}

void LocationManager::AddLocation(Location* loc)
{
	locations.push_back(loc);
}

Location* LocationManager::GetLocation(int id)
{
	for (auto loc : locations)
	{
		if (loc->GetLocationId() == id)
		{
			return loc;
		}
	}
	return nullptr;
}
