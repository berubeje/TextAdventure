#pragma once
#include "Location.h"
#include <vector>
#include "json.hpp"
class LocationManager
{
private:
	std::vector<Location*> locations;

public:
	LocationManager();
	~LocationManager();
	void CreateLocationsFromJSON(json::JSON& node);
	void AddLocation(Location* loc);
};

