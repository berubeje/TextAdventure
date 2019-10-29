#include "Enemy.h"
#include "Player.h"



//Enemy::Enemy(int loc, std::string name, std::string noun, bool alive, std::string aliveDesc, std::string killedDesc, std::string killedPlayerDesc)
//	:Obstacle(loc, name, noun), isAlive(alive), isAliveDescription(aliveDesc), killedDescription(killedDesc), killedPlayerDescription(killedPlayerDesc)
//{
//}

Enemy::Enemy()
{
	validVerbs.push_back("ATTACK");
}

Enemy::~Enemy()
{
}

std::string Enemy::GetDescription(int select)
{
	if (select == 1)
	{
		return isAliveDescription + " : " + commandNoun;
	}

	return "";
}

void Enemy::Initialize(json::JSON& node)
{
	//Enemy
	enemyName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	isAliveDescription = node["IsAliveDescription"].ToString();
	killedDescription = node["KilledDescription"].ToString();
	killedPlayerDescription = node["KilledPlayerDescription"].ToString();
	isAlive = node["IsAlive"].ToBool();
	triggerOnFriend = node["TriggerOnFriend"].ToBool();
}

void Enemy::Interact(std::string& verb)
{

}

void Enemy::KillEnemy()
{
	isAlive = false;
	std::cout << killedDescription + "\n" << std::endl;
}

void Enemy::KillPlayer(Player* player)
{
	std::cout << killedPlayerDescription + "\n" << std::endl;
	player->Die();
}

