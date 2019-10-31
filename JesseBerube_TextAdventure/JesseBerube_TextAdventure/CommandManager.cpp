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
#include "DatabaseManager.h"

CommandManager::CommandManager()
{
	currentPlayer = nullptr;
	currentFriend = nullptr;
}

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

	commands.emplace("PRESS", "*Press What?*");
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
	oneWordCommands.emplace("INVENTORY", std::bind(&CommandManager::ShowInventoryCommand, &CommandManager::Instance()));
	oneWordCommands.emplace("SAVE", std::bind(&CommandManager::SaveCommand, &CommandManager::Instance()));
	

	twoWordCommands.emplace("MOVE", std::bind(&CommandManager::MoveCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2));
	twoWordCommands.emplace("PICKUP", std::bind(&CommandManager::PickupCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2));
	twoWordCommands.emplace("DROP", std::bind(&CommandManager::DropCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2));
	twoWordCommands.emplace("GRAB", std::bind(&CommandManager::GrabFriendCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2));
	twoWordCommands.emplace("PRESS", std::bind(&CommandManager::PressCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2));

	verbTwoWordCommands.emplace("USE", std::bind(&CommandManager::TwoWordUseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	verbTwoWordCommands.emplace("ATTACK", std::bind(&CommandManager::TwoWordUseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	verbTwoWordCommands.emplace("READ", std::bind(&CommandManager::TwoWordUseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	verbTwoWordCommands.emplace("OPEN", std::bind(&CommandManager::OpenCloseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	verbTwoWordCommands.emplace("CLOSE", std::bind(&CommandManager::OpenCloseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	verbFourWordCommands.emplace("USE", std::bind(&CommandManager::FourWordUseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	verbFourWordCommands.emplace("ATTACK", std::bind(&CommandManager::FourWordUseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	verbFourWordCommands.emplace("READ", std::bind(&CommandManager::FourWordUseCommand, &CommandManager::Instance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	

	//This will be used to stop repeating nouns being added into the command list. Only one version of the noun is needed.

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

void CommandManager::ValidateAndExecuteCommand(std::string& com)
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

//Used to seperate the verb and the noun for execution
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

//Seperate all the words and put them in their proper place
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

//Using the function pointers and parameters to execute the commands
bool CommandManager::ExecuteCommand(std::string& verb)
{
	if (oneWordCommands.find(verb) != oneWordCommands.end())
	{
		return oneWordCommands[verb]();
	}
	else
	{
		std::cout << commands.find(verb)->second +"\n"<< std::endl;
	}
	return false;
}

bool CommandManager::ExecuteCommand(std::string& verb, std::string& noun, bool& invalidNoun)
{
	if (verbTwoWordCommands.find(verb) != verbTwoWordCommands.end())
	{
		return verbTwoWordCommands[verb](verb, noun, invalidNoun);
	}
	else if (twoWordCommands.find(verb) != twoWordCommands.end())
	{
		return twoWordCommands[verb](noun, invalidNoun);
	}
	std::cout << "*You cannot do that!*\n" << std::endl;
	return false;
}

bool CommandManager::ExecuteCommand(std::string& verb, std::string& noun, std::string& noun2, bool& invalidNoun)
{
	if (verbFourWordCommands.find(verb) != verbFourWordCommands.end())
	{
		return verbFourWordCommands[verb](verb, noun, noun2, invalidNoun);
	}
	else if (fourWordCommands.find(verb) != fourWordCommands.end())
	{
		return fourWordCommands[verb](noun, noun2, invalidNoun);
	}
	std::cout << "*You cannot do that!*\n" << std::endl;
	return false;
}

//Look command gets the description of the location, then all the game objects in the location
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

bool CommandManager::SaveCommand()
{
	FileManager::Instance().SaveFile();
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

	std::cout << output << std::endl;
	return true;
}

//The move command uses current location to get the direction from it, then checks if there are obstacles or enemies. If there is not, move
bool CommandManager::MoveCommand(std::string& dir, bool& invalidDir)
{
	if (invalidDir == true)
	{
		std::cout << "*Not a valid direction*\n" << std::endl;
		return false;
	}

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
			DatabaseManager::Instance().IncrementActions();


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

//Used to verb to see if it should open or close the door
bool CommandManager::OpenCloseCommand(std::string& verb, std::string& noun, bool& invalidNoun)
{

	if (invalidNoun == true)
	{
		std::cout << "*That door is not around here*\n" << std::endl;
		return false;
	}

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
				DatabaseManager::Instance().IncrementActions();
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

//Checks if the item is in the area, if it is, pick it up
bool CommandManager::PickupCommand(std::string& noun, bool& invalidNoun)
{
	if (invalidNoun == true)
	{
		std::cout << "*That item is not here*\n" << std::endl;
		return false;
	}
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

			DatabaseManager::Instance().IncrementActions();
			DatabaseManager::Instance().IncrementItemPickups();

			return true;
		}
	}
	std::cout << "*That item is not here*\n" << std::endl;
	return false;
}

//Check to see if the item is in the player's inventory. If it is, drop it
bool CommandManager::DropCommand(std::string& noun, bool& invalidNoun)
{
	if (invalidNoun == true)
	{
		std::cout << "*You do not have that item*\n" << std::endl;
		return false;
	}

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

			DatabaseManager::Instance().IncrementActions();

			return true;
		}
	}
	std::cout << "*You do not have that item*\n" << std::endl;
	return false;
}

//Uses the verb to attempt to use the item if the player has it
bool CommandManager::TwoWordUseCommand(std::string& verb, std::string& noun, bool& invalidNoun)
{
	if (invalidNoun == true)
	{
		std::cout << "*You do not have that item to use*\n" << std::endl;
		return false;
	}

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

//Uses the verb to attempt to use the item if the player has it
//After the item is found, it then needs to find what the item will be used on
bool CommandManager::FourWordUseCommand(std::string& verb, std::string& noun, std::string& noun2, bool& invalidNoun)
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

	if (foundItem == nullptr)
	{
		std::cout << "*You do not have that item to use.*\n" << std::endl;
		return false;
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

	std::cout << "*You cannot use that item on that.*\n" << std::endl;

	return false;
}

//Press command is currently just used for the puzzle, but could be used for other things if added to the game
bool CommandManager::PressCommand(std::string& noun, bool& invalidNoun)
{
	if (invalidNoun == true)
	{
		std::cout << "*There is nothing to press around*\n" << std::endl;
		return false;
	}
	for (auto obstacle : obstaclesInArea)
	{
		if (obstacle->GetCommandName() == noun)
		{
			if (obstacle->Interact(noun) == true)
			{

				DatabaseManager::Instance().IncrementActions();

				return true;
			}
			else
			{
				return false;
			}
		}
		//done so you dont need to type PUZZLE as a noun for every button input on the puzzle.
		else if (obstacle->GetCommandName() == "PUZZLE")
		{
			if (obstacle->Interact(noun) == true)
			{

				DatabaseManager::Instance().IncrementActions();

				return true;
			}
			else
			{
				return false;
			}
		}
	}
	std::cout << "*There is nothing to press around*\n" << std::endl;
	return false;
}

bool CommandManager::GrabFriendCommand(std::string& noun, bool& invalidNoun)
{
	if (invalidNoun == true)
	{
		std::cout << "*That is not your friend...*\n" << std::endl;
		return false;
	}

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
			DatabaseManager::Instance().IncrementActions();

			return true;
		}
	}
	std::cout << "*That is not your friend...*\n" << std::endl;
	return false;
}

//Used before everything I consider an action (is checked after using ATTACK)
//If an enemy is found, they kill the player
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

//Check for doors and barriers when moving. If a door or barrier is found, they stop the player. If the barrier is fatal, it kills the player
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

