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
	bool open;

	bool isPuzzle;
	std::multimap<std::string, int> puzzleCombo;
	int partOfPuzzle;

public:
	Door();
	//Door(int loc, std::string name,  std::string noun, std::string block ,bool state ,std::string open, std::string close, bool locked, bool puzzle);
	virtual ~Door();

	virtual bool CheckBlockage(std::string& dir);
	virtual std::string GetDescription(int select = 1);
	virtual void Initialize(json::JSON& node);
	virtual bool Interact(std::string& word);
	virtual bool GetStatus() { return isLocked; }
	virtual bool GetOpen() { return open; }
	//virtual void SetStatus(bool set) { open = set; }
	virtual void Resolve();

	static Obstacle* Create() { return new Door(); }
};

