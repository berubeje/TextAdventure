#pragma once
#include <map>
#include <string>

class Interactable;

class CommandManager
{
private:
	std::multimap<std::string, Interactable*> commandMap;
};

