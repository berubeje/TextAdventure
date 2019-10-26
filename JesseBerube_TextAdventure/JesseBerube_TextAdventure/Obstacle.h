#pragma once
#include <vector>
#include <string>
#include "json.hpp"
class Obstacle
{
protected:
	int locationId;
	std::string classType;
	std::vector<std::string> validVerbs;
	std::string commandNoun;
	std::string obstacleName;


public:
	Obstacle();
	Obstacle(int loc, std::string name, std::string comName);
	virtual ~Obstacle();

	const virtual int& GetLocation() { return locationId; }
	const virtual std::string& GetType() { return classType; }
    virtual std::vector<std::string>* GetValidVerbs() { return &validVerbs; }
	const virtual std::string& GetCommandName() { return commandNoun; }
	
	virtual std::string GetDescription(int select = 1) = 0;
	virtual void Initialize(json::JSON&) = 0;
	virtual void Interact(std::string& verb) = 0;
	virtual bool GetStatus() = 0;
	
};

