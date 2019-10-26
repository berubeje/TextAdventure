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
	virtual std::string GetDescription(int select = 1);
	virtual void Initialize(json::JSON& node);
	virtual void Interact(std::string& verb);
	virtual bool GetStatus() { return isSolved; }

	static Obstacle* Create() { return new Barrier(); }
};

