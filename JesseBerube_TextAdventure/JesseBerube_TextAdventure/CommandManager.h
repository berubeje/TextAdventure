#pragma once
#include <map>
#include <string>
#include <vector>
#include <list>

class Obstacle;
class Item;
class Player;
class LocationManager;
class ObstacleAndItemManager;

class CommandManager
{
private:
	//std::map<std::string, std::string> moveCommands;
	std::multimap<std::string, std::string> commands;
	std::list<Obstacle*> obstaclesInArea;
	std::list<Item*> itemsInArea;


public:
	inline static CommandManager& Instance() {
		static CommandManager instance;
		return instance;
	}

	void UpdateInteractablesInAreaList(int& id);
	void CreateCommands(std::vector<Obstacle*>* obstacleVec, std::vector<Item*>* itemVec);
	void ValidateAndExecuteCommand(std::string com);
	void LookCommand();


private:
	inline explicit CommandManager()
	{
	}

	inline ~CommandManager()
	{
	}

	inline explicit CommandManager(CommandManager const&)
	{
	}

	inline CommandManager& operator=(CommandManager const&)
	{
		return *this;
	}

	bool OneWordCommand(std::string& com);
	bool TwoWordCommand(std::string& com);
	bool FourWordCommand(std::string& com);
	bool ExecuteCommand(std::string& verb);
	bool ExecuteCommand(std::string& verb, std::string& noun);
	bool ExecuteCommand(std::string& verb, std::string& noun, std::string& preposition, std::string& noun2);


	void MoveCommand(std::string& dir);
	bool CheckForDoorAndBarrier(int& loc, std::string& dir);

};

