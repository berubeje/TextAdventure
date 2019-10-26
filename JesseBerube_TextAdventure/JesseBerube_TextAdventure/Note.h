#pragma once
#include "Item.h"
class Note :
	public Item
{
private:
	std::string writtenOnNote;

public:
	Note();
	//Note(int loc, std::string name, std::string noun ,std::string info, std::string writing);
	virtual ~Note();
	virtual void UseItem();

	virtual void Initialize(json::JSON& node);

	static Item* Create() { return new Note(); }
};

