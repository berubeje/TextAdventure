#pragma once
#include "Player.h"
#include "CommandManager.h"
#include "LocationManager.h"
class FileManager
{
private:
	LocationManager* locMgr;
	Player* player;
	CommandManager* cmdMgr;
public:
	FileManager(LocationManager* loc, Player* play, CommandManager* cmd);
	~FileManager();
	void LoadFile(bool loadSave);
	void SaveFile();
};

