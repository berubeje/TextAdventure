#include "InteractableManager.h"
#include "Door.h"
#include "Note.h"

InteractableManager::InteractableManager()
{
}

InteractableManager::~InteractableManager()
{
	for (auto inter: interactables )
	{
		delete inter;
	}
}

void InteractableManager::CreateInteractablesFromJSON(json::JSON& items, json::JSON& object)
{

	for (auto obj : object.ArrayRange())
	{
		Interactable* newObj = nullptr;
		if (obj["Class"].ToString() == "Door")
		{
			newObj = new Door(obj["Location"].ToInt(),obj["Command Noun"].ToString(), obj["Blocking Direction"].ToString(), obj["Open"].ToBool(), obj["Open Description"].ToString(), obj["Closed Description"].ToString());
			
			AddInteractableObject(newObj);
		}
	}

	for (auto item : items.ArrayRange())
	{
		Interactable* newItem = nullptr;

		if (item["Class"].ToString() == "Note")
		{
			newItem = new Note(item["Location"].ToInt(), item["Command Noun"].ToString(), item["Info"].ToString(), item["Written On Note"].ToString());

			AddInteractableObject(newItem);

		}
	}
}

void InteractableManager::AddInteractableObject(Interactable* inter)
{
	interactables.push_back(inter);
}

