#include "Door.h"

Door::Door(int loc, bool state, std::string open, std::string close)
	:Interactable(loc), opened(state), ifOpenDesc(open), ifClosedDesc(close)
{
}

Door::~Door()
{
}

void Door::AddVerbs()
{
}

void Door::Open()
{

}

void Door::Close()
{

}
