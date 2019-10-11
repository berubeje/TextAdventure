#include "CommandManager.h"
#include "Interactable.h"

CommandManager::CommandManager()
{
	commands.emplace("MOVE", "NORTH");
	commands.emplace("MOVE", "EAST");
	commands.emplace("MOVE", "WEST");
	commands.emplace("MOVE", "SOUTH");
	commands.emplace("MOVE", "UP");
	commands.emplace("MOVE", "DOWN");

	commands.emplace("LOOK", "");
	commands.emplace("USE", "");
	commands.emplace("PICKUP", "");
	commands.emplace("DROP", "");
	commands.emplace("OPEN", "");
	commands.emplace("CLOSE", "");
}

CommandManager::~CommandManager()
{

}

void CommandManager::CreateCommands(std::vector<Interactable*>* interVec)
{
	//This will be used to stop repeating nouns being added into the command list. Only one version of the noun is needed.
	//std::vector<std::string> existingNouns;

	for (auto inter : *interVec)
	{
		bool exists = false;
		std::string noun = inter->GetCommandName();
		std::vector<std::string>* verbs = inter->GetValidVerbs();
		
		//search to make sure the noun and verb combination is not already in the map, as we only need it once
		for(int i = 0; i != verbs->size(); i++)
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
				commands.emplace((*verbs)[i] ,noun);
			}
		}
	}
}

bool CommandManager::ValidateCommand(std::string com)
{
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

	com = com.substr(com.find_first_of(" \t")+1);

	bool validCommmand = false;
	
	for (auto comMap : commands)
	{
		if (comMap.first == verb && comMap.second == com)
		{
			validCommmand = true;
			break;
		}
	}

	if (validCommmand == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
