#pragma once
#include <iostream>
#include "FileManager.h"
#include "LocationManager.h"
#include "InteractableManager.h"
#include "CommandManager.h"
#include "Player.h"

class TextGame
{
private:
	FileManager* fileMgr;
	LocationManager* locMgr;
	InteractableManager* interMgr;
	CommandManager* cmdMgr;
	Player* player;
	
public:
	TextGame();
	~TextGame();
	bool Setup();
	void StartGame();
	void GameLoop();
	void AdjustString(std::string& resp);
};

