#include "Object.h"

Object::Object(std::string name, bool state, std::string trueDesc, std::string falseDesc)
{
	objectName = name;
	objectState = state;
	trueStateDescription = trueDesc;
	falseStateDescription = falseDesc;
}

Object::~Object()
{
}
