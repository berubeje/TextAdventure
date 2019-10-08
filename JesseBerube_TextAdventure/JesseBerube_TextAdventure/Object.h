#pragma once
#include <string>
#include "Interactable.h"
//THIS IS NOT BEING USED LIKE A GAME ENGINE OBJECT

class Object:public Interactable
{
public:

	Object();
	~Object();
	virtual void AddVerb();
	virtual int  GetLocation() { return locationId; };
	virtual bool ChangeState() = 0;
};

