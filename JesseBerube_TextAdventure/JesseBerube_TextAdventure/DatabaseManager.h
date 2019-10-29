#pragma once
class DatabaseManager
{
private:
	unsigned int playerActions;
	unsigned int playerItemPickups;
	unsigned int totalTimesPlayed;
	unsigned int totalPlayerDeaths;



public:
	inline static DatabaseManager& Instance() {
		static DatabaseManager instance;
		return instance;
	}


private:

	inline explicit DatabaseManager()
	{
	}

	inline ~DatabaseManager()
	{
	}

	inline explicit DatabaseManager(DatabaseManager const&)
	{
	}

	inline DatabaseManager& operator=(DatabaseManager const&)
	{
		return *this;
	}
};

