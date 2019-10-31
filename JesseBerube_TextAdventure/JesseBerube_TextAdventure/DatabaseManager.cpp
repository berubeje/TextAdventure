#include "DatabaseManager.h"
#include <iostream>


bool DatabaseManager::Initialize(std::string  path)
{
	databasePath = path;
	return ReadFromDatabase();
}

bool DatabaseManager::ReadFromDatabase()
{
	try
	{
		sqlite3* db = OpenDatabase();

		if (db == nullptr)
		{
			return false;
		}

		sqlite3_stmt* selectStmt;
		int result;

		result = sqlite3_prepare_v2(db, "SELECT TotalActions, TotalItemPickups, TotalTimesPlayed, TotalDeaths FROM PlayerInfo", -1, &selectStmt, 0);
		if (result != SQLITE_OK)
		{
			std::cout << sqlite3_errmsg(db);
			std::cout << "\nCould not prepare statement." << std::endl;
			return false;
		}

		if (sqlite3_step(selectStmt) == SQLITE_ROW)
		{
			totalActions = sqlite3_column_int(selectStmt, 0);
			totalItemPickups = sqlite3_column_int(selectStmt, 1);
			totalTimesPlayed = sqlite3_column_int(selectStmt, 2);
			totalPlayerDeaths = sqlite3_column_int(selectStmt, 3);
		}
		else
		{
			noRecords = true;
		}
		

		sqlite3_finalize(selectStmt);
		sqlite3_close(db);

		//std::cout << "Last error: " << sqlite3_errmsg(db) << std::endl;


		db = nullptr;
		return true;
	}
	catch (...)
	{
		std::cout << "Something went wrong with reading the database. Data will not be saved to database" << std::endl;
		return false;
	}
}

bool DatabaseManager::WriteToDatabase()
{
	if (readError == true)
	{
		return false;
	}

	try
	{
		sqlite3* db = OpenDatabase();

		if (db == nullptr)
		{
			return false;
		}

		int result;
		sqlite3_stmt* stmt;

		//If there is a record inside the database, update it, else create new record
		if (noRecords == false)
		{
			result = sqlite3_prepare_v2(db, "UPDATE PlayerInfo SET TotalActions = ?, TotalItemPickups = ?, TotalTimesPlayed = ?, TotalDeaths = ?", -1, &stmt, 0);
		}
		else
		{
			result = sqlite3_prepare_v2(db, "INSERT INTO PlayerInfo(TotalActions, TotalItemPickups, TotalTimesPlayed, TotalDeaths) VALUES (?, ?, ?, ?)", -1, &stmt, 0);
		}

		if (result != SQLITE_OK)
		{
			std::cout << sqlite3_errmsg(db);
			std::cout << "\nCould not prepare statement." << std::endl;
			return false;
		}

		sqlite3_bind_parameter_count(stmt);

		result = sqlite3_bind_int(stmt, 1, totalActions);
		if (result != SQLITE_OK)
		{
			std::cout << sqlite3_errmsg(db);
			return false;
		}

		result = sqlite3_bind_int(stmt, 2, totalItemPickups);
		if (result != SQLITE_OK)
		{
			std::cout << sqlite3_errmsg(db);
			return false;
		}

		result = sqlite3_bind_int(stmt, 3, totalTimesPlayed);
		if (result != SQLITE_OK)
		{
			std::cout << sqlite3_errmsg(db);
			return false;
		}

		result = sqlite3_bind_int(stmt, 4, totalPlayerDeaths);
		if (result != SQLITE_OK)
		{
			std::cout << sqlite3_errmsg(db);
			return false;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE)
		{
			std::cout << sqlite3_errmsg(db);
			return false;
		}
		
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		db = nullptr;
		return true;

	}
	catch (...)
	{
		std::cout << "Something went wrong with writing to the database. Data will not be saved to database" << std::endl;
		return false;
	}
}

sqlite3* DatabaseManager::OpenDatabase()
{
	sqlite3* db;
	int rc;

	rc = sqlite3_open(databasePath.c_str(), &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return nullptr;
	}

	return db;
}
