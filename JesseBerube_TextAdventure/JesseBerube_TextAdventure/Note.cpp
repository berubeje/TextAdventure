#include "Note.h"
#include <iostream>

//Note::Note(int loc, std::string name, std::string noun, std::string info, std::string writing)
//	:Item(loc, name, noun, info), writtenOnNote(writing)
//{
//}

Note::Note()
{
}

Note::~Note()
{
}

void Note::UseItem()
{
	std::cout << writtenOnNote << std::endl;
}

void Note::Initialize(json::JSON& node)
{
	//Obstacle
	interactableName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();


	//Item
	worldInfo = node["WorldInfo"].ToString();

	//Note
	writtenOnNote = node["WrittenOnNote"].ToString();
}
