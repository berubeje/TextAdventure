#pragma once
#include "Obstacle.h"
class Enemy :
	public Obstacle
{
private:
	bool isAlive;
	std::string isAliveDescription;
	std::string killedDescription;
	std::string killedPlayerDescription;


public:
	Enemy();
	//Enemy(int loc, std::string name, std::string noun, bool alive, std::string aliveDesc, std::string killedDesc, std::string killedPlayerDesc);
	virtual ~Enemy();

	virtual std::string GetDescription(int select = 1);
	virtual void Initialize(json::JSON& node);
	virtual void Interact(std::string& verb);
	virtual bool GetStatus() { return isAlive; }

	static Obstacle* Create() { return new Enemy(); }
};

