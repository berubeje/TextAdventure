#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(int loc, std::string name, std::string comName)
	:locationId(loc), interactableName(name), commandNoun(comName)
{
}

Obstacle::~Obstacle()
{

}
