#pragma once
#include <string>
class Item
{
private:
	std::string itemName;
	int locationId;
	std::string info;

public:
	Item();
	~Item();
};

