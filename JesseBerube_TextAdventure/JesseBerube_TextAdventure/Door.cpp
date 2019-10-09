#include "Door.h"
#include <iostream>

Door::Door(int loc, std::string name, bool state, std::string open, std::string close)
	:Interactable(loc, name), opened(state), ifOpenDesc(open), ifClosedDesc(close)
{
	validVerbs.push_back("OPEN");
	validVerbs.push_back("CLOSE");
}

Door::~Door()
{
}

//void Door::AddVerbs()
//{
//}

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
