#pragma once
#include "Item.h"
class Note :
	public Item
{
private:
	std::string writtenOnNote;

public:
	Note(int loc, std::string name, std::string info, std::string writing);
	virtual ~Note();
	virtual void UseItem();
	//virtual std::string GetDescription() { return info; }
};

