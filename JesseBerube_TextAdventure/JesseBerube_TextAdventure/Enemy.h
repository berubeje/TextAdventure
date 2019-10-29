#pragma once
#include "Obstacle.h"

class Player;

class Enemy
{
private:
	int locationId;
	std::vector<std::string> validVerbs;
	std::string commandNoun;
	std::string enemyName;

	bool isAlive;
	bool triggerOnFriend;
	std::string isAliveDescription;
	std::string killedDescription;
	std::string killedPlayerDescription;


public:
	Enemy();
	virtual ~Enemy();

	const int& GetLocation() { return locationId; }
	std::vector<std::string>* GetValidVerbs() { return &validVerbs; }
	const std::string& GetCommandName() { return commandNoun; }
	const std::string& GetName() { return enemyName; }

	std::string GetDescription(int select = 1);
	void Initialize(json::JSON& node);
	void Interact(std::string& verb);
	bool GetAlive() { return isAlive; }
	bool GetFriendTrigger() { return triggerOnFriend; }

	void KillEnemy();
	void KillPlayer(Player* player);

	static Enemy* Create() { return new Enemy(); }
};

