#pragma once
#include <string>
#include "Obstacle.h"
//THIS IS NOT BEING USED LIKE A GAME ENGINE OBJECT

class Object:public Obstacle
{
public:

	Object();
	~Object();
	virtual void AddVerb();
	virtual int  GetLocation() { return locationId; };
	virtual bool ChangeState() = 0;
};

