#pragma once

class Player;
class CommandManager;
class LocationManager;
class ItemManager;

class FileManager
{
private:
	LocationManager* locMgr;
	Player* player;
	ItemManager* itemMgr;
	CommandManager* cmdMgr;
public:
	FileManager(LocationManager* loc, Player* play, ItemManager* item, CommandManager* cmd);
	~FileManager();
	void LoadFile(bool loadSave);
	void SaveFile();
};

