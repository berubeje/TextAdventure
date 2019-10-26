
#include <iostream>
#include "TextGame.h"

using namespace std;

int main()
{

		bool success = TextGame::Instance().Setup();

		if (success)
		{
			TextGame::Instance().StartGame();
		}
		else
		{
			std::cout << "Something when wrong while setting up. Aborting application." << std::endl;
			return -1;
		}

}


