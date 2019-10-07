#pragma once
#include <string>

//THIS IS NOT BEING USED LIKE A GAME ENGINE OBJECT

class Object
{
private:
	std::string objectName;
	bool objectState;
	std::string trueStateDescription;
	std::string falseStateDescription;

public:

	Object(std::string name, bool state, std::string trueDesc, std::string falseDesc);
	~Object();
};

