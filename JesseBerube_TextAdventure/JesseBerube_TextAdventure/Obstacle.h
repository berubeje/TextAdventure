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

	const int& GetLocation() { return locationId; }
	const std::string& GetType() { return classType; }
	const std::string& GetCommandName() { return commandNoun; }
	const std::string& GetName() { return obstacleName; }
	std::vector<std::string>* GetValidVerbs() { return &validVerbs; }


	virtual bool CheckBlockage(std::string& dir) = 0;
	virtual std::string GetDescription() = 0;
	virtual void Initialize(json::JSON& node) = 0;
	virtual bool Interact(std::string& word) = 0;
	virtual bool GetOpen() = 0;
	virtual bool GetStatus() = 0;
	//virtual void SetStatus(bool set) = 0;
	virtual void Resolve() = 0;
	
	
};

