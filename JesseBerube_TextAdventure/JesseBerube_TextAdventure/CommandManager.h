#pragma once
#include <map>
#include <string>
#include <vector>
#include <list>
#include <functional>

class Obstacle;
class Item;
class Player;
class Friend;
class Enemy;
class LocationManager;
class GameObjectManager;

class CommandManager
{
private:
	//std::map<std::string, std::string> moveCommands;
	std::multimap<std::string, std::string> commands;

	std::map<std::string, std::function<bool()>> oneWordCommands;
	std::map<std::string, std::function<bool(std::string&, std::string&, bool&)>> twoWordCommands;
	std::map<std::string, std::function<bool(std::string&, std::string&, std::string&, bool&)>> fourWordCommands;


	std::list<Obstacle*> obstaclesInArea;
	std::list<Item*> itemsInArea;
	std::list<Enemy*> enemiesInArea;

	Player* currentPlayer;
	Friend* currentFriend;

	bool endGame = false;

public:
	inline static CommandManager& Instance() {
		static CommandManager instance;
		return instance;
	}

	void UpdateInteractablesInAreaList(int& id);
	void SetupCommandManager(std::vector<Obstacle*>& obstacleVec, std::vector<Item*>& itemVec, std::vector<Enemy*>& enemyVec);
	void ValidateAndExecuteCommand(std::string com);
	
	bool LookCommand();



private:
	inline explicit CommandManager()
	{
		currentPlayer = nullptr;
		currentFriend = nullptr;
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
	bool ExecuteCommand(std::string& verb, std::string& noun, bool& invalidNoun);
	bool ExecuteCommand(std::string& verb, std::string& noun, std::string& noun2, bool& invalidNoun);

	bool ShowInventoryCommand();
	bool MoveCommand(std::string& dir);
	bool OpenCloseCommand(std::string& verb, std::string& noun);
	bool UseCommand(std::string& verb, std::string& noun, std::string& noun2);
	bool UseCommand(std::string& verb, std::string& noun, bool& invalidNoun);
	bool PickupCommand(std::string& noun);
	bool DropCommand(std::string& noun);
	bool PressCommand(std::string& noun);
	bool GrabFriendCommand(std::string& noun);

	bool CheckForDoorAndBarrier(int& loc, std::string& dir);
	bool CheckForEnemy();
};

