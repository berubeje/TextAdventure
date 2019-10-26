#include "Door.h"
#include <iostream>

Door::Door()
{
}

//Door::Door(int loc, std::string name, std::string noun, std::string block, bool state, std::string open, std::string close, bool locked, bool puzzle)
//	:Obstacle(loc, name, noun), blockingDirection(block),  open(state), openDescription(open), closedDescription(close), isLocked(locked), isPuzzle(puzzle)
//{
//
//	validVerbs.push_back("OPEN");
//	validVerbs.push_back("CLOSE");
//}

Door::~Door()
{
}

std::string Door::GetDescription(int select)
{
	if (select == 1)
	{
		if (open == true)
		{
			return openDescription;
		}
		else
		{
			return closedDescription;
		}
	}
}

void Door::Interact(std::string& verb)
{
	if (verb == "OPEN")
	{
		if (open == false)
		{
			open = true;
			std::cout << "The " + obstacleName + " has been opened." << std::endl;
		}
		else
		{
			std::cout << "The " + obstacleName + " is already open." << std::endl;
		}
	}
	else if (verb == "CLOSED")
	{
		if (open == true)
		{
			open = false;
			std::cout << "The " + obstacleName + " has been closed." << std::endl;
		}
		else
		{
			std::cout << "The " + obstacleName + " is already closed." << std::endl;
		}
	}
}

void Door::Initialize(json::JSON& node)
{
	//Interactables
	obstacleName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();


	//Door
	blockingDirection = node["BlockingDirection"].ToString();
	open = node["Open"].ToBool();
	openDescription = node["OpenDescription"].ToString();
	closedDescription = node["ClosedDescription"].ToString();
	isLocked = node["IsLocked"].ToBool();
	isPuzzle = node["IsPuzzle"].ToBool();

}


