#pragma once
#include <map>
#include <string>
#include <vector>

class Interactable;
class Player;
class LocationManager;
class InteractableManager;

class CommandManager
{
private:
	//std::map<std::string, std::string> moveCommands;
	std::multimap<std::string, std::string> commands;
	LocationManager* locMgr;
	InteractableManager* interMgr;
	Player* player;

public:
	CommandManager(LocationManager* loc, InteractableManager* inter, Player* play);
	~CommandManager();
	void CreateCommands(std::vector<Interactable*>* interVec);
	void ValidateAndExecuteCommand(std::string com);
	bool OneWordCommand(std::string& com);
	bool TwoWordCommand(std::string& com);
	bool FourWordCommand(std::string& com);
	bool ExecuteCommand(std::string& verb);
	bool ExecuteCommand(std::string& verb, std::string& noun);
	bool ExecuteCommand(std::string& verb, std::string& noun, std::string& preposition, std::string& noun2);
	void LookCommand();
};

