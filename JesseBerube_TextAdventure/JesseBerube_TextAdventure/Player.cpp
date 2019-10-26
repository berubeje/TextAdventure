#include "Player.h"
#include "ObstacleAndItemManager.h"

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
	inventory = ObstacleAndItemManager::Instance().GetItemsByLocationId(inventoryLocation);
}

void Player::AddToInventory(Item* item)
{
	inventory.push_back(item);
}

void Player::RemoveFromInventory(Item* item)
{
	inventory.remove(item);
}
