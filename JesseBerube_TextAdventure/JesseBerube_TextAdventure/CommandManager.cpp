#include "CommandManager.h"
#include "Obstacle.h"
#include "Item.h"
#include "ObstacleAndItemManager.h"
#include "LocationManager.h"
#include "Location.h"
#include "Player.h"
#include <iostream>


void CommandManager::UpdateInteractablesInAreaList(int& id)
{
	itemsInArea.clear();
	obstaclesInArea.clear();
	obstaclesInArea = ObstacleAndItemManager::Instance().GetObstaclesByLocationId(id);
	itemsInArea = ObstacleAndItemManager::Instance().GetItemsByLocationId(id);
}

void CommandManager::CreateCommands(std::vector<Obstacle*>* obstacleVec, std::vector<Item*>* itemVec)
{

	//Moving Commands
	commands.emplace("MOVE", "*Move in what direction?*");
	commands.emplace("MOVE", "NORTH");
	commands.emplace("MOVE", "EAST");
	commands.emplace("MOVE", "WEST");
	commands.emplace("MOVE", "SOUTH");
	commands.emplace("MOVE", "UP");
	commands.emplace("MOVE", "DOWN");

	//Verbs
	commands.emplace("LOOK", "");
	commands.emplace("USE", "*Use what?*");
	commands.emplace("PICKUP", "*Pickup what?*");
	commands.emplace("DROP", "*Drop what?*");
	commands.emplace("OPEN", "*Open what?*");
	commands.emplace("CLOSE", "*Close What*");
	commands.emplace("ATTACK", "*Attack what with what?*");

	commands.emplace("GRAB", "*Grab what?*");
	commands.emplace("GRAB", "FRIEND");

	//Preposition
	commands.emplace("ON", "");
	commands.emplace("WITH", "");


	//This will be used to stop repeating nouns being added into the command list. Only one version of the noun is needed.
	//std::vector<std::string> existingNouns;

	for (auto ob : *obstacleVec)
	{
		bool exists = false;
		std::string noun = ob->GetCommandName();
		std::vector<std::string>* verbs = ob->GetValidVerbs();

		//search to make sure the noun and verb combination is not already in the map, as we only need it once
		for (int i = 0; i != verbs->size(); i++)
		{
			for (auto command : commands)
			{
				if (command.first == (*verbs)[i] && command.second == noun)
				{
					exists = true;
				}
			}

			if (exists == false)
			{
				commands.emplace((*verbs)[i], noun);
			}
		}
	}

	for (auto it : *itemVec)
	{
		bool exists = false;
		std::string noun = it->GetCommandName();
		std::vector<std::string>* verbs = it->GetValidVerbs();

		//search to make sure the noun and verb combination is not already in the map, as we only need it once
		for (int i = 0; i != verbs->size(); i++)
		{
			for (auto command : commands)
			{
				if (command.first == (*verbs)[i] && command.second == noun)
				{
					exists = true;
				}
			}

			if (exists == false)
			{
				commands.emplace((*verbs)[i], noun);
			}
		}
	}
}

void CommandManager::ValidateAndExecuteCommand(std::string com)
{


	//Get a count of how many words in string. This counts the white spaces between words, so 3 white spaces = 4 words
	int numOfWords = 1;

	for (auto c : com)
	{
		if (c == ' ')
		{
			numOfWords++;
		}
	}

	if (numOfWords == 1)
	{
		if (OneWordCommand(com) == false)
		{
			std::cout << "*This command is invalid*" << std::endl;
		}
	}
	else if (numOfWords == 2)
	{
		if(TwoWordCommand(com) == false)
		{
			std::cout << "*This command is invalid*" << std::endl;
		}
	}
	else if (numOfWords == 4)
	{
		if(FourWordCommand(com) == false)
		{
			std::cout << "*This command is invalid*" << std::endl;
		}
	}
	else
	{
		std::cout << "*This command is invalid*" << std::endl;
		return;
	}
}

bool CommandManager::OneWordCommand(std::string& com)
{
	bool validCommand = false;
	for (auto comMap : commands)
	{
		if (comMap.first == com)
		{
			validCommand = true;
			break;
		}
	}

	if (validCommand == true)
	{
		return ExecuteCommand(com);
	}
	else
	{
		return false;
	}

}

bool CommandManager::TwoWordCommand(std::string& com)
{
	bool validCommand = false;
	std::string verb;
	for (auto c : com)
	{
		if (c == ' ')
		{
			break;
		}
		else
		{
			verb = verb + c;
		}
	}

	com = com.substr(com.find_first_of(" \t") + 1);

	for (auto comMap : commands)
	{
		if (comMap.first == verb && comMap.second == com)
		{
			validCommand = true;
			break;
		}
	}

	if (validCommand == true)
	{
		return ExecuteCommand(verb, com);
	}
	else
	{
		return false;
	}
}

bool CommandManager::FourWordCommand(std::string& com)
{
	bool validCommand = false;

	std::string verb;
	std::string noun;
	std::string preposition;
	std::string noun2;

	int word = 0;

	for (auto c : com)
	{
		if (c == ' ')
		{
			word++;
			if (word == 3)
			{
				break;
			}
		}
		else
		{
			switch (word)
			{
			case 0:
				verb = verb + c;
				break;

			case 1:
				noun = noun + c;
				break;

			case 2:
				preposition = preposition + c;
				break;

			case 3:
				noun2 = noun2 + c;

			default:
				break;
			}
		}
	}

	for (auto comMap : commands)
	{
		if (comMap.first == verb && comMap.second == noun)
		{
			for (auto comMapPreposition : commands)
			{
				if (comMapPreposition.first == preposition)
				{
					for (auto comMapNoun2 : commands)
					{
						if (comMapNoun2.second == noun2)
						{
							validCommand = true;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}

	if (validCommand == true)
	{
		return ExecuteCommand(verb, noun, preposition, noun2);
	}
	else
	{
		return false;
	}
}

bool CommandManager::ExecuteCommand(std::string& verb)
{
	if (verb == "LOOK")
	{
		LookCommand();
	}
	else
	{
		std::cout << commands.find(verb)->second << std::endl;
	}

	return true;
}

bool CommandManager::ExecuteCommand(std::string& verb, std::string& noun)
{
	if (verb == "MOVE")
	{
		MoveCommand(noun);
	}
	return true;
}

bool CommandManager::ExecuteCommand(std::string& verb, std::string& noun, std::string& preposition, std::string& noun2)
{
	return false;
}

void CommandManager::LookCommand()
{

	std::string lookDescription;

	Location* loc = LocationManager::Instance().GetLocation(Player::Instance().GetLocation());

	lookDescription += loc->GetLocationDescription() + "\n";

	lookDescription += ObstacleAndItemManager::Instance().GetInteractableDescriptions(Player::Instance().GetLocation());
	std::cout << "\n"<< std::endl;
	std::cout << lookDescription << std::endl;
}

void CommandManager::MoveCommand(std::string& dir)
{
	std::cout << "You moved" << std::endl;
	Location* loc = LocationManager::Instance().GetLocation(Player::Instance().GetLocation());

	Direction* direct = loc->GetDirection(dir);

	if (direct != nullptr)
	{
		int newLoc = direct->GetToLocation();
		if (LocationManager::Instance().GetLocation(newLoc) != nullptr)
		{
			Player::Instance().ChangeLocation(newLoc);
			UpdateInteractablesInAreaList(newLoc);

			LookCommand();
		}
		else
		{
			std::cout << direct->GetFailure() << std::endl;
		}
	}
	else
	{
		std::cout << "*You cannot go that way*" << std::endl;
	}
}

bool CommandManager::CheckForDoorAndBarrier(int& loc, std::string& dir)
{
	//for (auto inter : interactablesInArea)
	//{
	//	if (inter->GetClassType() == "Door")
	//	{
	//		
	//	}
	//	else if(inter->GetClassType() == "Barrier")
	//	{

	//	}
	//}
	return false;
}

