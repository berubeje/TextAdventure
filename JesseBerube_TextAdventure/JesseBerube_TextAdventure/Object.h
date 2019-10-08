#pragma once
#include <string>
#include "Interactable.h"
//THIS IS NOT BEING USED LIKE A GAME ENGINE OBJECT

class Object:public Interactable
{
private:
	std::string objectName;
	bool objectState;
	std::string trueStateDescription;
	std::string falseStateDescription;

public:

	Object(std::string name, bool state, std::string trueDesc, std::string falseDesc);
	~Object();
	virtual void AddVerb();
	virtual int  GetLocation() { return locationId; };
	virtual bool ChangeState() = 0;
};

