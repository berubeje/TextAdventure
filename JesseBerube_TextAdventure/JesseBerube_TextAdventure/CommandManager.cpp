#include "CommandManager.h"
#include "Obstacle.h"
#include "Item.h"
#include "GameObjectManager.h"
#include "LocationManager.h"
#include "Location.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include "FileManager.h"
#include "TextGame.h"



void CommandManager::UpdateInteractablesInAreaList(int& id)
{
	itemsInArea.clear();
	obstaclesInArea.clear();
	enemiesInArea.clear();
	obstaclesInArea = GameObjectManager::Instance().GetObstaclesByLocationId(id);
	itemsInArea = GameObjectManager::Instance().GetItemsByLocationId(id);
	enemiesInArea = GameObjectManager::Instance().GetEnemiesByLocationId(id);
}

void CommandManager::SetupCommandManager(std::vector<Obstacle*>& obstacleVec, std::vector<Item*>& itemVec, std::vector<Enemy*>& enemyVec)
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

	commands.emplace("PRESS", "UP");
	commands.emplace("PRESS", "DOWN");
	commands.emplace("PRESS", "LEFT");
	commands.emplace("PRESS", "RIGHT");
	commands.emplace("PRESS", "A");
	commands.emplace("PRESS", "B");
	commands.emplace("PRESS", "START");
	commands.emplace("PRESS", "SELECT");
	
	
	commands.emplace("SAVE", "");
	commands.emplace("INVENTORY", "");

	//Preposition
	commands.emplace("ON", "USE");
	commands.emplace("WITH", "ATTACK");


	//Setup command function pointers
	//oneWordCommands.emplace("LOOK", std::function<bool()>(CommandManager::Instance().LookCommand));
	oneWordCommands.emplace("LOOK", std::bind(&CommandManager::LookCommand, &CommandManager::Instance()));
	
	
	twoWordCommands.emplace("USE", std::function<bool(std::string&, std::string&, bool&)>(CommandManager::Instance().UseCommand));
	

	//This will be used to stop repeating nouns being added into the command list. Only one version of the noun is needed.
	//std::vector<std::string> existingNouns;

	for (auto ob : obstacleVec)
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

	for (auto it : itemVec)
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

	for (auto en : enemyVec)
	{
		bool exists = false;
		std::string noun = en->GetCommandName();
		std::vector<std::string>* verbs = en->GetValidVerbs();

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

	currentPlayer = GameObjectManager::Instance().GetPlayer();
	currentFriend = GameObjectManager::Instance().GetFriend();
	UpdateInteractablesInAreaList(currentPlayer->GetLocation());
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
			std::cout << "*This command is invalid*\n" << std::endl;
		}
	}
	else if (numOfWords == 2)
	{
		if(TwoWordCommand(com) == false)
		{
			std::cout << "*This command is invalid*\n" << std::endl;
		}
	}
	else if (numOfWords == 4)
	{
		if(FourWordCommand(com) == false)
		{
			std::cout << "*This command is invalid*\n" << std::endl;
		}
	}
	else
	{
		std::cout << "*This command is invalid*\n" << std::endl;
		return;
	}
}

bool CommandManager::OneWordCommand(std::string& com)
{
	bool validVerb = false;
	for (auto comMap : commands)
	{
		if (comMap.first == com)
		{
			validVerb = true;
			break;
		}
	}

	if (validVerb == true)
	{
		ExecuteCommand(com);
		return true;
	}
	else
	{
		return false;
	}

}

bool CommandManager::TwoWordCommand(std::string& com)
{
	bool validVerb = false;
	bool invalidNoun = false;
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
			validVerb = true;
			invalidNoun = false;
			break;
		}
		else if(comMap.first == verb)
		{
			validVerb = true;
			invalidNoun = true;
		}
	}

	if (validVerb == true)
	{
		ExecuteCommand(verb, com, invalidNoun);
		return true;
	}
	else
	{
		return false;
	}
}

bool CommandManager::FourWordCommand(std::string& com)
{
	bool validVerb = false;
	bool invalidNoun = false;

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
				if (comMapPreposition.first == preposition && comMapPreposition.second == verb)
				{
					validVerb = true;
					invalidNoun = false;
					break;
				}
				else
				{
					validVerb = true;
					invalidNoun = true;
				}
			}
			break;
		}
		else if(comMap.first == verb)
		{
			validVerb = true;
			invalidNoun = true;
		}
	}

	if (validVerb == true)
	{
		ExecuteCommand(verb, noun, noun2, invalidNoun);
		return true;
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
	else if (verb == "SAVE")
	{
		FileManager::Instance().SaveFile();
	}
	else if (verb == "INVENTORY")
	{
		ShowInventoryCommand();
	}
	else
	{
		std::cout << commands.find(verb)->second << std::endl;
	}

	return true;
}

bool CommandManager::ExecuteCommand(std::string& verb, std::string& noun, bool& invalidNoun)
{
	if (verb == "MOVE")
	{
		if (invalidNoun == true)
		{
			std::cout << "*Not a valid direction*\n" << std::endl;
			return false;
		}
		MoveCommand(noun);
	}
	else if(verb == "OPEN" || verb == "CLOSE")
	{
		if (invalidNoun == true)
		{
			std::cout << "*There is no door around*\n" << std::endl;
			return false;
		}
		OpenCloseCommand(verb, noun);
	}
	else if (verb == "PRESS")
	{
		if (invalidNoun == true)
		{
			std::cout << "*There is nothing to press around*\n" << std::endl;
			return false;
		}
		PressCommand(noun);
	}
	else if(verb == "PICKUP")
	{
		if (invalidNoun == true)
		{
			std::cout << "*That item is not here*\n" << std::endl;
			return false;
		}
		PickupCommand(noun);
	}
	else if (verb == "DROP")
	{
		if (invalidNoun == true)
		{
			std::cout << "*You do not have that item*\n" << std::endl;
			return false;
		}
		DropCommand(noun);
	}
	else if (verb == "USE" || verb == "ATTACK" || verb == "READ")
	{
		if (invalidNoun == true)
		{
			std::cout << "*You do not have that item*\n" << std::endl;
			return false;
		}
		bool test = false;
		UseCommand(verb, noun, test);
	}
	else if (verb == "GRAB")
	{
		if (invalidNoun == true)
		{
			std::cout << "*That is not your friend...*\n" << std::endl;
			return false;
		}
		GrabFriendCommand(noun);
	}

	return true;
}

bool CommandManager::ExecuteCommand(std::string& verb, std::string& noun, std::string& noun2, bool& invalidNoun)
{
	if (verb == "USE" || verb == "ATTACK" || verb == "READ")
	{
		if (invalidNoun == true)
		{
			std::cout << "*You do not have that item or what you are trying to use it on does not exist*\n" << std::endl;
			return false;
		}
		UseCommand(verb, noun, noun2);
	}

	return true;
}

bool CommandManager::LookCommand()
{
	int currentLocation = currentPlayer->GetLocation();
	
	std::string lookDescription;

	Location* loc = LocationManager::Instance().GetLocation(currentLocation);

	lookDescription += loc->GetLocationDescription() + "\n";

	for (auto obstacle : obstaclesInArea)
	{	
		lookDescription += obstacle->GetDescription() + "\n";
	}	
	for (auto item : itemsInArea)
	{	
		lookDescription += item->GetDescription() + "\n";
	}	
	for (auto enemy : enemiesInArea)
	{	
		if (enemy->GetAlive() == true)
		{
			if (enemy->GetFriendTrigger() == true)
			{
				if (currentPlayer->GetFriend() == true)
				{
					lookDescription += enemy->GetDescription() + "\n";
				}
			}
			else
			{
				lookDescription += enemy->GetDescription() + "\n";
			}
		}
	}

	std::cout << std::endl;
	std::cout << lookDescription << std::endl;
	return true;
}

bool CommandManager::ShowInventoryCommand()
{
	std::string output = "";

	for (auto item : currentPlayer->GetInventory())
	{
		output += item->GetName() + " : " + item->GetCommandName() + "\n";
	}

	if (output == "")
	{
		output = "Inventory is empty\n";
	}

	std::cout << output;
	return true;
}

bool CommandManager::MoveCommand(std::string& dir)
{
	int currentLocation = currentPlayer->GetLocation();

	Location* loc = LocationManager::Instance().GetLocation(currentLocation);

	Direction* direct = loc->GetDirection(dir);

	if (direct != nullptr)
	{
		int newLoc = direct->GetToLocation();
		Location* theNewLocation = LocationManager::Instance().GetLocation(newLoc);
		if (theNewLocation != nullptr && CheckForDoorAndBarrier(currentLocation, direct->GetDirection()) == false && CheckForEnemy() == false)
		{

			currentPlayer->ChangeLocation(newLoc);
			UpdateInteractablesInAreaList(newLoc);

			if (theNewLocation->GetEndLocation() == true && currentPlayer->GetFriend() == true)
			{
				TextGame::Instance().EndGame();
				endGame = true;
			}

			if (endGame == false)
			{
				LookCommand();
			}

			return true;
		}
		else
		{
			if (currentPlayer->GetDead() == false)
			{
				if (direct->GetFailure() != "")
				{
					std::cout << direct->GetFailure() + "\n" << std::endl;
				}
			}
			else
			{
				UpdateInteractablesInAreaList(currentPlayer->GetLocation());
				LookCommand();
				currentPlayer->SetDead(false);
			}
			return false;
		}
	}
	else
	{
		std::cout << "*You cannot go that way* \n" << std::endl;
		return false;
	}
}

bool CommandManager::OpenCloseCommand(std::string& verb, std::string& noun)
{
	for (auto obstacle : obstaclesInArea)
	{
		if (obstacle->GetCommandName() == noun)
		{
			if (CheckForEnemy() == true)
			{
				return false;
			}
			if (obstacle->Interact(verb) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CommandManager::PickupCommand(std::string& noun)
{
	for (auto item : itemsInArea)
	{
		if (item->GetCommandName() == noun)
		{
			if (CheckForEnemy() == true)
			{
				return false;
			}
			currentPlayer->AddToInventory(item);
			item->SetLocation(0);
			std::cout << "*You picked up the " + item->GetName() + "*\n"  << std::endl;

			return true;
		}
	}
	std::cout << "*That item is not here*\n" << std::endl;
	return false;
}

bool CommandManager::DropCommand(std::string& noun)
{
	for (auto item : currentPlayer->GetInventory())
	{
		if (item->GetCommandName() == noun)
		{
			if (CheckForEnemy() == true)
			{
				return false;
			}
			currentPlayer->RemoveFromInventory(item);
			item->SetLocation(currentPlayer->GetLocation());
			std::cout << "*You dropped the " + item->GetName() + "*\n" << std::endl;
			return true;
		}
	}
	std::cout << "*You do not have that item*\n" << std::endl;
	return false;
}

bool CommandManager::UseCommand(std::string& verb, std::string& noun, bool& invalidNoun)
{
	
	for (auto item : currentPlayer->GetInventory())
	{
		if (item->GetCommandName() == noun)
		{
			item->UseItem(verb);
			if (CheckForEnemy() == true)
			{
				return false;
			}
			return true;
		}
	}
	std::cout << "*You do not have that item to use*\n" << std::endl;
	return false;
}

bool CommandManager::PressCommand(std::string& noun)
{
	for (auto obstacle : obstaclesInArea)
	{
		//done so you dont need to type PUZZLE for every button input
		if (obstacle->GetCommandName() == "PUZZLE")
		{
			if (obstacle->Interact(noun) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (obstacle->GetCommandName() == noun)
		{
			if (obstacle->Interact(noun) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CommandManager::GrabFriendCommand(std::string& noun)
{
	if (noun == "FRIEND")
	{
		if (currentFriend->GetFriendLocation() == currentPlayer->GetLocation())
		{
			if (CheckForEnemy() == true)
			{
				return false;
			}
			currentPlayer->SetFriend(true);
			std::cout << "*You found your friend! Now you just need to get back to the mansion!*\n" << std::endl;

			return true;
		}
	}
	std::cout << "*That is not your friend...*\n" << std::endl;
	return false;
}

bool CommandManager::CheckForEnemy()
{
	for (auto enemy : enemiesInArea)
	{
		if (enemy->GetAlive() == true)
		{
			if (enemy->GetFriendTrigger() == true)
			{
				if (currentPlayer->GetFriend() == true)
				{
					enemy->KillPlayer(currentPlayer);
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				enemy->KillPlayer(currentPlayer);
				return true;
			}
		}
	}

	return false;
}


bool CommandManager::UseCommand(std::string& verb, std::string& noun, std::string& noun2)
{
	Item* foundItem = nullptr;

	for (auto item : currentPlayer->GetInventory())
	{
		if (item->GetCommandName() == noun || item->GetCommandName() == noun2)
		{
			foundItem = item;
			break;
		}
	}

	for (auto obstacle : obstaclesInArea)
	{
		if (obstacle->GetCommandName() == noun2)
		{
			if (CheckForEnemy() == true)
			{
				return false;
			}
			foundItem->UseItem(verb, obstacle);
			return true;
		}
	}

	for (auto enemy : enemiesInArea)
	{
		if (enemy->GetCommandName() == noun)
		{
			if (enemy->GetAlive() == true)
			{
				if (enemy->GetFriendTrigger() == true)
				{
					if (currentPlayer->GetFriend() == true)
					{
						foundItem->UseItem(verb, enemy);
						if (CheckForEnemy() == true)
						{
							return false;
						}
						return true;
					}
					else
					{
						std::cout << "Cannot find what you want to attack.\n" << std::endl;
						return false;
					}
				}
				else
				{
					foundItem->UseItem(verb, enemy);
					if (CheckForEnemy() == true)
					{
						return false;
					}
					return true;
				}
			}
			else
			{
				std::cout << "Cannot find what you want to attack.\n" << std::endl;
				return false;
			}
		}
	}

	if (foundItem == nullptr)
	{
		std::cout << "*You do not have that item to use.*\n" << std::endl;
	}
	else
	{
		std::cout << "*You cannot use that item on that.*\n" << std::endl;
	}

	return false;
}

bool CommandManager::CheckForDoorAndBarrier(int& loc, std::string& dir)
{
	for (auto obstacle : obstaclesInArea)
	{
		if (obstacle->CheckBlockage(dir) == false)
		{
			//No doors or barrier blocking path, so return false
			return false;
		}
		else
		{
			//Door or Barrier blocking path. If barrier is fatal, it will kill player.

			if (obstacle->GetType() == "Barrier"  && obstacle->GetStatus() == true)
			{
				currentPlayer->Die();
			}
			return true;
		}
	}
	return false;
}

