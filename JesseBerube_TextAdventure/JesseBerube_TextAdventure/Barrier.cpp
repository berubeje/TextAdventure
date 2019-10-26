#include "Barrier.h"

//Barrier::Barrier(int loc, std::string name, std::string noun, std::string block, std::string unsolvedDesc, std::string fatalDesc, bool solved, bool fatal)
//	:Obstacle(loc, name, noun), blockingDirection(block), unsolvedDescription(unsolvedDesc), fatalDescription(fatalDesc), isSolved(solved), isFatal(fatal)
//{
//}

Barrier::Barrier()
{
}

Barrier::~Barrier()
{
}

std::string Barrier::GetDescription(int select)
{
	if (select = 1)
	{
		if (isSolved == false)
		{
			return unsolvedDescription;
		}
		else
		{
			return solvedDescription;
		}
	}
	else if (select = 2)
	{
		return fatalDescription;
	}
	return "";
}

void Barrier::Interact(std::string& verb)
{
}

void Barrier::Initialize(json::JSON& node)
{
	//Interactables
	obstacleName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();

	//Barrier
	blockingDirection = node["BlockingDirection"].ToString();
	unsolvedDescription = node["UnsolvedDescription"].ToString();
	solvedDescription = node["UnsolvedDescription"].ToString();
	fatalDescription = node["FatalDescription"].ToString();
	isSolved = node["IsSolved"].ToBool();
	isFatal = node["IsFatal"].ToBool();
}



