#include "Enemy.h"



//Enemy::Enemy(int loc, std::string name, std::string noun, bool alive, std::string aliveDesc, std::string killedDesc, std::string killedPlayerDesc)
//	:Obstacle(loc, name, noun), isAlive(alive), isAliveDescription(aliveDesc), killedDescription(killedDesc), killedPlayerDescription(killedPlayerDesc)
//{
//}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

std::string Enemy::GetDescription(int select)
{
	if (select = 1)
	{
		return isAliveDescription;
	}

	return "";
}

void Enemy::Initialize(json::JSON& node)
{
	//Interactables
	obstacleName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();


	//Enemy
	isAliveDescription = node["IsAliveDescription"].ToBool();
	killedDescription = node["KilledDescription"].ToString();
	killedPlayerDescription = node["KilledPlayerDescription"].ToBool();
	isAlive = node["IsAlive"].ToBool();
}

void Enemy::Interact(std::string& verb)
{

}

