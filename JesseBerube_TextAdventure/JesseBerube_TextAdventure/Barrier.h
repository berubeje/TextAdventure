#pragma once
#include "Obstacle.h"
class Barrier: public Obstacle
{
private:
	std::string blockingDirection;
	std::string unsolvedDescription;
	std::string solvedDescription;
	std::string fatalDescription;
	bool isSolved;
	bool isFatal;

public:
	Barrier();
	//Barrier(int loc, std::string name, std::string noun, std::string block, std::string unsolvedDesc, std::string fatalDesc, bool solved, bool fatal);
	virtual ~Barrier();
	
	virtual bool CheckBlockage(std::string& dir);
	virtual std::string GetDescription(int select = 1);
	virtual void Initialize(json::JSON& node);
	virtual bool Interact(std::string& word);
	virtual bool GetStatus() { return isFatal; }
	virtual bool GetOpen() { return isSolved; }
	//virtual void SetStatus(bool set) { isSolved = set; }
	virtual void Resolve();

	static Obstacle* Create() { return new Barrier(); }
};

