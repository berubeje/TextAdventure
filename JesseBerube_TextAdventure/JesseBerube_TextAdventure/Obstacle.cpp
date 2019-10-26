#include "Obstacle.h"

Obstacle::Obstacle()
{
	locationId = -1;
}

Obstacle::Obstacle(int loc, std::string name, std::string comName)
	:locationId(loc), obstacleName(name), commandNoun(comName)
{
}

Obstacle::~Obstacle()
{

}
