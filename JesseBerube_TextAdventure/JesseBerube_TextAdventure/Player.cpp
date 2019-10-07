#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetupPlayer(json::JSON& node)
{
	location = node["Location"].ToInt();
	hasFriend = node["Has Friend"].ToBool();
}

void Player::ChangeLocation(int loc)
{
	location = loc;
}

void Player::SetFriend(bool set)
{
	hasFriend = set;
}
