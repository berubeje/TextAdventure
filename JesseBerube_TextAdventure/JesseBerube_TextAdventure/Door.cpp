#include "Door.h"
#include <iostream>

Door::Door(int loc, std::string name, std::string block, bool state, std::string open, std::string close)
	:Interactable(loc, name), blockingDirection(block),  opened(state), ifOpenDesc(open), ifClosedDesc(close)
{
	validVerbs.push_back("OPEN");
	validVerbs.push_back("CLOSE");
}

Door::~Door()
{
}

void Door::Open()
{
	if (opened == false)
	{
		opened = true;
		std::cout << "The door has been opened." << std::endl;
	}
	else
	{
		std::cout << "The door is already opened." << std::endl;
	}
}

void Door::Close()
{
	if (opened == true)
	{
		opened = false;
		std::cout << "The door has been closed." << std::endl;
	}
	else
	{
		std::cout << "The door is already closed." << std::endl;
	}
}

std::string Door::GetDescription()
{
	if (opened == true)
	{
		return ifOpenDesc;
	}
	else
	{
		return ifClosedDesc;
	}
}
