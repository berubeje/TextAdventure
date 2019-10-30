#include "Player.h"
#include "GameObjectManager.h"
#include "DatabaseManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetupPlayer(json::JSON& node)
{
	location = node["PlayerLocation"].ToInt();
	hasFriend = node["HasFriend"].ToBool();
}

void Player::ChangeLocation(int loc)
{
	location = loc;
}

void Player::SetFriend(bool set)
{
	hasFriend = set;
}

void Player::SetupInventory()
{
	//A location of 0 is considered player inventory. Location of -1 means it is not in play anymore
	int inventoryLocation = 0;
	inventory = GameObjectManager::Instance().GetItemsByLocationId(inventoryLocation);
}

void Player::Die()
{
	isDead = true;
	std::list<Item*>::iterator i = inventory.begin();
	while (i != inventory.end())
	{
		if ((*i)->GetType() != "Weapon")
		{
			(*i)->SetLocation(location);
			i = inventory.erase(i);
		}
		else
		{
			i++;
		}
	}

	std::cout << "You lost all your items where you died, but you kept your weapon if you had one. You are sent back to the start.\n" << std::endl;

	if (hasFriend == true)
	{
		hasFriend = false;
		std::cout << "Your friend is sent back to where you found him.\n" << std::endl;
	}
	DatabaseManager::Instance().IncrementTotalDeaths();
	location = 1;
}