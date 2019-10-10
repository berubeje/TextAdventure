#include "FileManager.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"
#include "InteractableManager.h"
#include "LocationManager.h"


#include <fstream>


FileManager::FileManager(LocationManager* loc, InteractableManager* inter ,Player* play, CommandManager* cmd)
	:locMgr(loc), interMgr(inter), player(play), cmdMgr(cmd)
{
	
}

FileManager::~FileManager()
{

}

void FileManager::LoadFile(bool newGame)
{
	if (newGame)
	{
		std::ifstream inputStream("NewGameFile.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());

		json::JSON doc = json::JSON::Load(str);

		_ASSERT_EXPR(doc.hasKey("PlayerInfo"), "Player Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Items"), "Items Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Objects"), "Objects Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Locations"), "Locations Node Not Found. Time to crash!");

		locMgr->CreateLocationsFromJSON(doc["Locations"]);
		interMgr->CreateInteractablesFromJSON(doc["Items"], doc["Objects"]);
		player->SetupPlayer(doc["PlayerInfo"]);
	}
	else
	{

	}
}

void FileManager::SaveFile()
{

}
