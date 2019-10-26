#include "FileManager.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"
#include "ObstacleAndItemManager.h"
#include "LocationManager.h"
#include "Friend.h"

#include <exception>
#include <fstream>



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

		LocationManager::Instance().CreateLocationsFromJSON(doc["Locations"]);
		ObstacleAndItemManager::Instance().CreateInteractablesFromJSON(doc["Items"], doc["Objects"]);
		Player::Instance().SetupPlayer(doc["PlayerInfo"]);
		Player::Instance().SetupInventory();

		json::JSON friendNode = doc["Friend"];
		Friend::SetFriendLocation(friendNode["FriendLocation"].ToInt());

		CommandManager::Instance().CreateCommands(ObstacleAndItemManager::Instance().GetObstacleArray(),ObstacleAndItemManager::Instance().GetItemArray());
		CommandManager::Instance().UpdateInteractablesInAreaList(Player::Instance().GetLocation());

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
