#include "LocationManager.h"
#include "Location.h"


void LocationManager::CreateLocationsFromJSON(json::JSON& node)
{
	for (auto loc:node.ArrayRange())
	{
		Location* newLoc = new Location(loc["LocationId"].ToInt(), loc["LocationName"].ToString(),loc["Description"].ToString());
	
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
