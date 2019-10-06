#pragma once
#include <iostream>
#include "FileManager.h"
#include "LocationManager.h"
#include "CommandManager.h"
#include "Player.h"

class TextGame
{
private:
	FileManager* fileMgr;
	LocationManager* locMgr;
	CommandManager* cmdMgr;
	Player* player;
	
public:
	TextGame();
	~TextGame();
	bool Setup();
	void StartGame();
	void GameLoop();
};

