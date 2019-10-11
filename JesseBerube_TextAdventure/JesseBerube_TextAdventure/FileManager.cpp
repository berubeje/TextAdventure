#include "FileManager.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"
#include "InteractableManager.h"
#include "LocationManager.h"
#include <exception>

#include <fstream>


FileManager::FileManager(LocationManager* loc, InteractableManager* inter ,Player* play, CommandManager* cmd)
	:locMgr(loc), interMgr(inter), player(play), cmdMgr(cmd)
{
	
}

FileManager::~FileManager()
{

}


bool FileManager::LoadFile(bool newGame)
{
	std::string filePath;
	if (newGame)
	{
		filePath = "NewGameFile.json";
	}
	else
	{

	}

	try {
		std::ifstream inputStream(filePath);
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());

		json::JSON doc = json::JSON::Load(str);

		_ASSERT_EXPR(doc.hasKey("PlayerInfo"), "Player Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Items"), "Items Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Objects"), "Objects Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Locations"), "Locations Node Not Found. Time to crash!");

		locMgr->CreateLocationsFromJSON(doc["Locations"]);
		interMgr->CreateInteractablesFromJSON(doc["Items"], doc["Objects"]);
		player->SetupPlayer(doc["PlayerInfo"]);

		cmdMgr->CreateCommands(interMgr->GetInteractableArray());

		return true;
	}
	catch (std::exception e)
	{
		std::cout << "Issue reading file! Check file" << std::endl;
		return false;
	}
}

void FileManager::SaveFile()
{

}
