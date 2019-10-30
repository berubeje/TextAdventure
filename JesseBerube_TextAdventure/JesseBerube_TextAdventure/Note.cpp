#include "Note.h"
#include <iostream>
#include "DatabaseManager.h"

//Note::Note(int loc, std::string name, std::string noun, std::string info, std::string writing)
//	:Item(loc, name, noun, info), writtenOnNote(writing)
//{
//}

Note::Note()
{
	validVerbs.push_back("READ");
}

Note::~Note()
{
}

//Note does not need a noun,
void Note::UseItem(std::string verb)
{
	if (verb == "USE" || verb == "READ")
	{
		std::cout << writtenOnNote+"\n" << std::endl;
		DatabaseManager::Instance().IncrementActions();
	}
}

void Note::UseItem(std::string verb, Enemy* enemy)
{
	if (verb == "USE" || verb == "READ")
	{
		std::cout << "*You cannot use the "+ itemName + " that way*\n" << std::endl;
	}
}

void Note::UseItem(std::string verb, Obstacle* obstacle)
{
	if (verb == "USE" || verb == "READ")
	{
		std::cout << "*You cannot use the " + itemName + " that way*\n" << std::endl;
	}

}

void Note::Initialize(json::JSON& node)
{
	//Item
	itemName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();
	worldInfo = node["WorldInfo"].ToString();

	//Note
	writtenOnNote = node["WrittenOnNote"].ToString();
}
