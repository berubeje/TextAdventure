#pragma once
#include <iostream>
#include "FileManager.h"
#include "LocationManager.h"
#include "GameObjectManager.h"
#include "CommandManager.h"
#include "Player.h"

class TextGame
{
private:
	//FileManager* fileMgr;
	//LocationManager* locMgr;
	////GameObjectManager* interMgr;
	////CommandManager* cmdMgr;
	//Player* player;

	bool endGame = false;
	
public:

	inline static TextGame& Instance() {
		static TextGame instance;
		return instance;
	}


	bool Setup();
	void StartGame();
	void GameLoop();
	void AdjustString(std::string& resp);
	void EndGame();

private:
	inline explicit TextGame()
	{
	}

	inline ~TextGame()
	{
	}

	inline explicit TextGame(TextGame const&)
	{
	}

	inline TextGame& operator=(TextGame const&)
	{
		return *this;
	}
};

