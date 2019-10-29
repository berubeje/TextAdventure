#include "TextGame.h"
#include <algorithm>
#include <regex>



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
		if (FileManager::Instance().LoadFile(true) == false)
		{
			return false;
		}
	}
	else
	{
		if (FileManager::Instance().LoadFile(false) == false)
		{

			return false;
		}
	}
}

void TextGame::StartGame()
{
	GameLoop();
}

void TextGame::GameLoop()
{
	std::string response;
	CommandManager::Instance().LookCommand();
	std::getline(std::cin, response);
	do
	{
		try
		{

			std::getline(std::cin, response);

			AdjustString(response);

			if (response == "QUIT")
			{
				return;
			}

			std::cout << std::endl;
			CommandManager::Instance().ValidateAndExecuteCommand(response);

			if (endGame == true)
			{
				return;
			}

		}
		catch (int e)
		{
		}
	} while (true);
}


//Used to remove extra spaces and change command to upper case
void TextGame::AdjustString(std::string& response)
{
	bool whiteSpace = false;

	response = std::regex_replace(response, std::regex("^\\s+"), std::string(""));

	response = std::regex_replace(response, std::regex("\\s+$"), std::string(""));

	auto i = response.begin();
	while (i != response.end())
	{
		if (*i == ' ')
		{
			if (whiteSpace == false)
			{
				whiteSpace = true;
				i++;
			}
			else
			{
				i = response.erase(i);
			}
		}
		else
		{
			whiteSpace = false;
			i++;
		}
	}

	transform(response.begin(), response.end(), response.begin(), ::toupper);
}

void TextGame::EndGame()
{
	std::cout << "You made it back to the mansion with your friend! You escaped the strange world safely! Thank you for playing!" << std::endl;
	endGame = true;
}
