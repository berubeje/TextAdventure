#pragma once
#include <map>
#include <string>
#include <vector>

class Interactable;

class CommandManager
{
private:
	//std::map<std::string, std::string> moveCommands;
	std::multimap<std::string, std::string> commands;

public:
	CommandManager();
	~CommandManager();
	void CreateCommands(std::vector<Interactable*>* interVec);
};

