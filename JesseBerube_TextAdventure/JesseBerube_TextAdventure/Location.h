#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include "Direction.h"

class Location
{
private:
	int locationID;
	std::string locationName;
	std::string description;
	std::vector<Direction*> directions;
	bool endLocation;


public:
	Location(int id, std::string name, std::string desc, bool end);
	~Location();
	void CreateDirectionsFromJSON(json::JSON& node);
	void AddDirection(Direction* dir);
	Direction* GetDirection(std::string dir);
	int GetLocationId() { return locationID;}
	std::string GetLocationDescription() { return description; }
	bool GetEndLocation() { return endLocation; }
};

