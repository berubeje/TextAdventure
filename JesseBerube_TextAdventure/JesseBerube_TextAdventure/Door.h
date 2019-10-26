#pragma once
#include "Obstacle.h"
#include "json.hpp"
class Door :
	public Obstacle
{
private:
	std::string blockingDirection;
	std::string openDescription;
	std::string closedDescription;
	bool isLocked;
	bool isPuzzle;
	bool open;

public:
	Door();
	//Door(int loc, std::string name,  std::string noun, std::string block ,bool state ,std::string open, std::string close, bool locked, bool puzzle);
	virtual ~Door();
	virtual std::string GetDescription(int select = 1);
	virtual void Initialize(json::JSON& node);
	virtual void Interact(std::string& verb);
	virtual bool GetStatus() { return open; }

	static Obstacle* Create() { return new Door(); }
};

