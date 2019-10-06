
#include <iostream>
#include "TextGame.h"
using namespace std;
int main()
{
	TextGame* game = new TextGame();
	bool success = game->Setup();

	if (success)
	{

	}
	else
	{

	}

	delete game;
}


