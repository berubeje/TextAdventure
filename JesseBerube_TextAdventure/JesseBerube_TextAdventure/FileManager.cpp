#include "FileManager.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"
#include "GameObjectManager.h"
#include "LocationManager.h"
#include "Friend.h"

#include <exception>
#include <fstream>
#include "DatabaseManager.h"



bool FileManager::LoadFile(bool newGame)
{
	
	if (newGame)
	{
		loadedFile = "NewGameFile.json";
	}
	else
	{
		loadedFile = "LoadGameFile.json";
	}

	try {
		std::ifstream inputStream(loadedFile);

		_ASSERT_EXPR(inputStream.good(), "File Not Found. Time to crash!");

		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());

		json::JSON doc = json::JSON::Load(str);

		_ASSERT_EXPR(doc.hasKey("PlayerInfo"), "Player Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Friend"), "Friend Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Items"), "Items Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Obstacles"), "Obstacles Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Enemies"), "Obstacles Node Not Found. Time to crash!");
		_ASSERT_EXPR(doc.hasKey("Locations"), "Locations Node Not Found. Time to crash!");

		LocationManager::Instance().CreateLocationsFromJSON(doc["Locations"]);
		GameObjectManager::Instance().CreateInteractablesFromJSON(doc["Items"], doc["Obstacles"], doc["Enemies"]);
		GameObjectManager::Instance().CreatePlayerAndFriendFromJSON(doc["PlayerInfo"], doc["Friend"]);
		CommandManager::Instance().SetupCommandManager(GameObjectManager::Instance().GetObstacleArray(),GameObjectManager::Instance().GetItemArray(), GameObjectManager::Instance().GetEnemyArray());

		DatabaseManager::Instance().Initialize("TextAdventureDatabase.db");

		return true;
	}
	catch (std::exception e)
	{
		std::cout << "Issue reading file! Check file" << std::endl;
		return false;
	}
}

//Saving the file creates a copy of the newgamefile if it is being, then writes the necessary changes to the file
//If the game was loaded in using previously saved data, it just uses the loaded file
void FileManager::SaveFile()
{
	try
	{
		Player* savePlayer = GameObjectManager::Instance().GetPlayer();
		Friend* saveFriend = GameObjectManager::Instance().GetFriend();
		std::vector<Obstacle*> obstaclesSave = GameObjectManager::Instance().GetObstacleArray();
		std::vector<Item*> itemsSave = GameObjectManager::Instance().GetItemArray();
		std::vector<Enemy*> enemiesSave = GameObjectManager::Instance().GetEnemyArray();

		//Create a copy of NewGameFile
		if (loadedFile == "NewGameFile.json")
		{
			std::ifstream src(loadedFile);
			std::ofstream dst("LoadGameFile.json");
			loadedFile = "LoadGameFile.json";

			dst << src.rdbuf();
		}

		std::ifstream inputStream(loadedFile);
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());

		json::JSON doc = json::JSON::Load(str);

		inputStream.close();

		//Needs to be a reference or changes will not be saved. We only need to save location ids and state of game objects
		for (auto& obJSON : doc["Obstacles"].ArrayRange())
		{
			for (auto ob : obstaclesSave)
			{
				if (ob->GetName() == obJSON["Name"].ToString())
				{
					if (ob->GetType() == "Door")
					{
						obJSON["Open"] = ob->GetOpen();
						break;
					}
					else if (ob->GetType() == "Barrier")
					{
						obJSON["IsSolved"] = ob->GetOpen();
						break;
					}
				}
			}
		}

		for (auto& itemJSON : doc["Items"].ArrayRange())
		{
			for (auto item : itemsSave)
			{
				if (item->GetName() == itemJSON["Name"].ToString())
				{
					itemJSON["LocationId"] = item->GetLocation();
					break;
				}
			}
		}

		for (auto& enemyJSON : doc["Enemies"].ArrayRange())
		{
			for (auto enemy : enemiesSave)
			{
				if (enemy->GetName() == enemyJSON["Name"].ToString())
				{
					enemyJSON["IsAlive"] = enemy->GetAlive();
					break;
				}
			}
		}

		json::JSON& playerNode = doc["PlayerInfo"];

		playerNode["PlayerLocation"] = savePlayer->GetLocation();
		playerNode["HasFriend"] = savePlayer->GetFriend();

		json::JSON& friendNode = doc["Friend"];

		friendNode["FriendLocation"] = saveFriend->GetFriendLocation();

		std::ofstream out("LoadGameFile.json");
		out << doc.dump() << std::endl;

		std::cout << "Saving Successful!\n" << std::endl;

	}
	catch (std::exception e)
	{
		std::cout << "Saving failed...\n" << std::endl;
	}
}
