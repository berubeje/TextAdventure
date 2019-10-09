#pragma once
#include <vector>
#include <string>
class Interactable
{
protected:
	int locationId;
	std::vector<std::string> validVerbs;
	std::string commandName;

public:
	Interactable(int loc, std::string comName);
	virtual ~Interactable();
	//virtual void AddVerbs() = 0;
	virtual int GetLocation() = 0;
	virtual std::string GetCommandName() = 0;
};

