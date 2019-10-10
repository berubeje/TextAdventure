#pragma once

class Player;
class CommandManager;
class LocationManager;
class InteractableManager;

class FileManager
{
private:
	LocationManager* locMgr;
	InteractableManager* interMgr;
	Player* player;
	CommandManager* cmdMgr;

public:
	FileManager(LocationManager* loc, InteractableManager* inter, Player* play, CommandManager* cmd);
	~FileManager();
	void LoadFile(bool loadSave);
	void SaveFile();
};

