#pragma once
#include <vector>
#include <string>
class Interactable
{
protected:
	int locationId;
	std::vector<std::string> validVerbs;
	std::string worldInfo;

public:
	Interactable();
	virtual ~Interactable();
	virtual void AddVerbs() = 0;
	virtual int GetLocation() = 0;
};

