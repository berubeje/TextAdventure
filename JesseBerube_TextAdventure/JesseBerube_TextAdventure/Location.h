#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include "Direction.h"
#include "Object.h"
class Location
{
private:
	int locationID;
	std::string locationName;
	std::string description;
	std::vector<Direction*> directions;
	std::vector<Object*> objects;

public:
	Location(int id, std::string name, std::string desc);
	~Location();
	void CreateDirectionsFromJSON(json::JSON& node);
	void CreateObjectsFromJSON(json::JSON& node);
	void AddDirection(Direction* dir);
	void AddObject(Object* obj);

};

