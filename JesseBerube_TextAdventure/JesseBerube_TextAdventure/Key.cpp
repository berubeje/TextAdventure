#include "Key.h"


Key::Key()
{
}

Key::~Key()
{
}

void Key::UseItem()
{

}

void Key::Initialize(json::JSON& node)
{
	//Obstacle
	interactableName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();


	//Item
	worldInfo = node["WorldInfo"].ToString();

	//Note
	doorBarrierName = node["DoorBarrierName"].ToString();
}

