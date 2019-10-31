#include "Door.h"
#include <iostream>

Door::Door()
{
	validVerbs.push_back("OPEN");
	validVerbs.push_back("CLOSE");


}


Door::~Door()
{
}

bool Door::CheckBlockage(std::string& dir)
{
	if (blockingDirection == dir && open == false)
	{
		std::cout << GetDescription() + "\n" << std::endl;
		return true;
	}
	return false;
}

std::string Door::GetDescription()
{

	if (open == true)
	{
		return openDescription + " : " + commandNoun;
	}
	else
	{
		return closedDescription + " : " + commandNoun;
	}


	return "";
}

bool Door::Interact(std::string& word)
{
	//Open the door if its closed
	if (word == "OPEN")
	{
		if (open == false)
		{
			if (isLocked == false)
			{
				open = true;
				std::cout << "The " + obstacleName + " has been opened.\n" << std::endl;
				return true;
			}
			else
			{
				std::cout << "The " + obstacleName + " is locked.\n" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "The " + obstacleName + " is already open.\n" << std::endl;
			return false;
		}
	}
	//close the door if its open
	else if (word == "CLOSE")
	{
		if (open == true)
		{
			open = false;
			std::cout << "The " + obstacleName + " has been closed.\n" << std::endl;
			return true;
		}
		else
		{
			std::cout << "The " + obstacleName + " is already closed.\n" << std::endl;
			return false;
		}
	}
	//This uses a counter to check what position of the vector the player is currently in.
	//If the input does not match where the player is in the puzzle, the counter resets to 0
	else if (isPuzzle == true && isLocked == true && (word == "UP" || word == "DOWN" || word == "LEFT" || word == "RIGHT" || word == "B" || word == "A" || word == "START" || word == "SELECT"))
	{
		for (auto puz : puzzleCombo)
		{
			if (puz.first == word && puz.second == partOfPuzzle)
			{
				partOfPuzzle++;
				std::cout << "DING! Correct input!\n" << std::endl;

				//Puzzle is complete. Open the door
				if (puzzleCombo.size() < partOfPuzzle)
				{
					isLocked = false;
					open = true;

					std::cout << "The puzzle clicks once more and opens wide, allowing passage!\n" << std::endl;


					return true;
				}

				return true;
			}
		}

		std::cout << "BZZT! Resetting input!\n" << std::endl;
		partOfPuzzle = 1;
		return true;

	}
	else
	{
		std::cout << "You cannot do that with the " + obstacleName + ".\n" << std::endl;
		return false;
	}

	return false;
}

void Door::Resolve()
{
	isLocked = false;
	std::cout << "The " + obstacleName + " unlocks!\n" << std::endl;
}

void Door::Initialize(json::JSON& node)
{
	//Obstacle
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

	//The puzzle solution is hardcoded in, but not the door its attached to 
	if (isPuzzle)
	{
		partOfPuzzle = 1;

		validVerbs.push_back("PRESS");

		puzzleCombo.emplace("UP", 1);
		puzzleCombo.emplace("UP", 2);
		puzzleCombo.emplace("DOWN", 3);
		puzzleCombo.emplace("DOWN", 4);
		puzzleCombo.emplace("LEFT", 5);
		puzzleCombo.emplace("RIGHT", 6);
		puzzleCombo.emplace("LEFT", 7);
		puzzleCombo.emplace("RIGHT", 8);
		puzzleCombo.emplace("B", 9);
		puzzleCombo.emplace("A", 10);
		puzzleCombo.emplace("START", 11);
	}

}



