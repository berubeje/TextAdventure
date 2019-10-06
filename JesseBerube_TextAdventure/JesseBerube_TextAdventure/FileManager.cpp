#include "FileManager.h"
#include "json.hpp"

#include <fstream>


FileManager::FileManager(LocationManager* loc, Player* play, CommandManager* cmd)
{
	locMgr = loc;
	player = play;
	cmdMgr = cmd;

}

FileManager::~FileManager()
{

}

void FileManager::LoadFile(bool newGame)
{
	if (newGame)
	{
		std::ifstream source("NewGameFile.json");
		std::ofstream dest("temp.json");

		dest << source.rdbuf();
	}
	else
	{

	}
}

void FileManager::SaveFile()
{

}
