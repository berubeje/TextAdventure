#pragma once
#include "Interactable.h"
class Door :
	public Interactable
{
private:
	std::string blockingDirection;
	bool opened;
	std::string ifOpenDesc;
	std::string ifClosedDesc;

public:
	Door(int loc, std::string name, std::string block ,bool state ,std::string open, std::string close);
	virtual ~Door();
    void Open();
	void Close();
};

