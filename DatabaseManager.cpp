#include <iostream>
#include "libraries.h"
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const std::string& name) : db(nullptr), dbName(name)
{
	int exit = sqlite3_open(dbName.c_str(), &db);
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error opening the database: " << sqlite3_errmsg(db) << std::endl;
	}
	else
	{
		std::cout << "Successfully opened database! " << std::endl;
	}
}
DatabaseManager::~DatabaseManager()
{
	if (db)
	{
		sqlite3_close(db);
		std::cout << "Database closed! " << std::endl;

	}
}
bool DatabaseManager::execute(const std::string& sql)
{
	char* msg = nullptr;
	int exit = sqlite3_exec(db, sql.c_str(), NULL, NULL, &msg);
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error executing query: " << msg << std::endl;
		sqlite3_free(msg);
		return false;
	}
	return true;
}
