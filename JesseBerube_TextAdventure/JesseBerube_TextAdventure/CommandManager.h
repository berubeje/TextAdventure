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
	std::multimap<std::string, std::string> commands;

	std::map<std::string, std::function<bool()>> oneWordCommands;
	std::map<std::string, std::function<bool(std::string&, bool&)>> twoWordCommands;

	//Not used in this version, but added incase new commands are added
	std::map<std::string, std::function<bool(std::string&, std::string&, bool&)>> fourWordCommands;

	//Some commands needs the verb used when executing
	std::map<std::string, std::function<bool(std::string&, std::string&, bool&)>> verbTwoWordCommands;
	std::map<std::string, std::function<bool(std::string&, std::string&, std::string&, bool&)>> verbFourWordCommands;


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
	void ValidateAndExecuteCommand(std::string& com);
	
	bool LookCommand();



private:
	CommandManager();

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
	bool SaveCommand();
	bool MoveCommand(std::string& dir, bool& invalidDir);
	bool OpenCloseCommand(std::string& verb, std::string& noun, bool& invalidNoun);
	bool FourWordUseCommand(std::string& verb, std::string& noun, std::string& noun2, bool& invalidNoun);
	bool TwoWordUseCommand(std::string& verb, std::string& noun, bool& invalidNoun);
	bool PickupCommand(std::string& noun, bool& invalidNoun);
	bool DropCommand(std::string& noun, bool& invalidNoun);
	bool PressCommand(std::string& noun, bool& invalidNoun);
	bool GrabFriendCommand(std::string& noun, bool& invalidNoun);

	bool CheckForDoorAndBarrier(int& loc, std::string& dir);
	bool CheckForEnemy();
};

