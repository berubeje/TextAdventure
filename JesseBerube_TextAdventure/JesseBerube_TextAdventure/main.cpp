
#include <iostream>
#include "TextGame.h"
using namespace std;
int main()
{
	TextGame* game = new TextGame();
	bool success = game->Setup();

	if (success)
	{
		game->StartGame();
	}
	else
	{
		std::cout << "Something when wrong while setting up. Aborting application." << std::endl;
		return -1;
	}

	delete game;
}


