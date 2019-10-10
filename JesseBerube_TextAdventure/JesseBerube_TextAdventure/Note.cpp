#include "Note.h"
#include <iostream>

Note::Note(int loc, std::string name, std::string info, std::string writing)
	:Item(loc, name, info), writtenOnNote(writing)
{
}

Note::~Note()
{
}

void Note::UseItem()
{
	std::cout << writtenOnNote << std::endl;
}
