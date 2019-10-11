#include "TextGame.h"

TextGame::TextGame()
{
	cmdMgr = new CommandManager();
	locMgr = new LocationManager();
	interMgr = new InteractableManager();
	player = new Player();
	fileMgr = new FileManager(locMgr, interMgr, player, cmdMgr);
}

TextGame::~TextGame()
{
	delete fileMgr;
	delete player;
	delete interMgr;
	delete locMgr;
	delete cmdMgr;
}


bool TextGame::Setup()
{
	std::cout << "Your friend has gone missing! The last you saw him, he was talking about going to an abandoned mansion to see if he could find any treasure. It has been a week now without any contact with him. You now set off for the mansion to see if you can find any clues to his disappearance..." << std::endl;
	std::cout << std::endl;
	std::cout << "*Would you like to load your save, or start a new game?*" << std::endl;
	std::cout << std::endl;
	std::cout << "*N = NEW, L = LOAD*" << std::endl;

	
	char response;

	try
	{
		std::cin >> response;
		response = toupper(response);
	}
	catch (int e)
	{
	}

	while (response != 'N' && response != 'L')
	{
		std::cout << "*Invalid input! Please type in 'N' for new game or 'L' to load you save*" << std::endl;
		std::cout << std::endl;
		std::cout << "*N = NEW, L = LOAD*" << std::endl;

		try
		{
			std::cin >> response;
			response = toupper(response);
		}
		catch (int e)
		{
		}
	}

	if (response == 'N')
	{
		if (fileMgr->LoadFile(true) == false)
		{
			return false;
		}
	}
	else
	{
		if (fileMgr->LoadFile(false) == false)
		{
			return false;
		}
	}

	return true;
}

void TextGame::StartGame()
{

}

void TextGame::GameLoop()
{

}
