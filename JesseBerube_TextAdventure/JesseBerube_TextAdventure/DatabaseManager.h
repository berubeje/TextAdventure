#pragma once

#include <string>
#include "sqlite3.h"

class DatabaseManager
{
private:
	unsigned int totalActions;
	unsigned int totalItemPickups;
	unsigned int totalTimesPlayed;
	unsigned int totalPlayerDeaths;

	std::string databasePath;
	bool noRecords;
	bool readError;


public:
	inline static DatabaseManager& Instance() {
		static DatabaseManager instance;
		return instance;
	}

	bool Initialize(std::string path);

	bool ReadFromDatabase();
	bool WriteToDatabase();
	sqlite3* OpenDatabase();

	void IncrementActions() { totalActions++; }
	void IncrementItemPickups() { totalItemPickups++; }
	void IncrementTotalTimesPlay() { totalTimesPlayed++; }
	void IncrementTotalDeaths() { totalPlayerDeaths++; }



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

