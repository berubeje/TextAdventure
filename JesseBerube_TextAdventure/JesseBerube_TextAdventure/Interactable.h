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
	const virtual int GetLocation() { return locationId; }
    virtual std::vector<std::string>* GetValidVerbs() { return &validVerbs; }
	const virtual std::string GetCommandName() { return commandName; }
};

