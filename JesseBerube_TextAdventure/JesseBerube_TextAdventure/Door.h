#pragma once
#include "Interactable.h"
class Door :
	public Interactable
{
private:
	bool opened;
	std::string ifOpenDesc;
	std::string ifClosedDesc;

public:
	Door(int loc, std::string name, bool state ,std::string open, std::string close);
	virtual ~Door();
    void Open();
	void Close();
};

