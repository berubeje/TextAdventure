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

bool Barrier::CheckBlockage(std::string& dir)
{
	if (blockingDirection == dir && isSolved == false)
	{
		if (isFatal == false)
		{
			std::cout << GetDescription() + "\n" << std::endl;
		}
		else
		{
			std::cout << fatalDescription + "\n" << std::endl;
		}
		return true;
	}
	return false;
}

std::string Barrier::GetDescription()
{
	if (isSolved == false)
	{
		return unsolvedDescription + " : " + commandNoun;
	}

	return "";
}

bool Barrier::Interact(std::string& word)
{

	return false;
}

void Barrier::Resolve()
{
	isSolved = true;
	std::cout << solvedDescription + "\n" << std::endl;
}


void Barrier::Initialize(json::JSON& node)
{
	//Obstacle
	obstacleName = node["Name"].ToString();
	locationId = node["LocationId"].ToInt();
	commandNoun = node["CommandNoun"].ToString();
	classType = node["ClassName"].ToString();

	//Barrier
	blockingDirection = node["BlockingDirection"].ToString();
	unsolvedDescription = node["UnsolvedDescription"].ToString();
	solvedDescription = node["SolvedDescription"].ToString();
	fatalDescription = node["FatalDescription"].ToString();
	isSolved = node["IsSolved"].ToBool();
	isFatal = node["IsFatal"].ToBool();
}



