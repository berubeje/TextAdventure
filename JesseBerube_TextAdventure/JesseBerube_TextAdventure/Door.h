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
	Door(int loc, bool state ,std::string open, std::string close);
	virtual ~Door();
	virtual void AddVerbs();
    void Open();
	void Close();
};

