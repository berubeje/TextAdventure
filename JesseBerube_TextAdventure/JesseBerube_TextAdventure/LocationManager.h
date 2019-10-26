#pragma once
#include <vector>
#include "json.hpp"
#include "Location.h"
class LocationManager
{
private:
	std::vector<Location*> locations;

public:
	inline static LocationManager& Instance() {
		static LocationManager instance;
		return instance;
	}

	void CreateLocationsFromJSON(json::JSON& node);
	void AddLocation(Location* loc);
	Location* GetLocation(int id);

private:
	inline explicit LocationManager()
	{
	}

	inline ~LocationManager()
	{
		for (auto loc : locations)
		{
			delete loc;
		}
	}

	inline explicit LocationManager(LocationManager const&)
	{
	}

	inline LocationManager& operator=(LocationManager const&)
	{
		return *this;
	}
};

