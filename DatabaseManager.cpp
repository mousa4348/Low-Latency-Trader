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
void DatabaseManager::databaseCheck(DatabaseManager& db, std::string& userID)
{
	std::string sql = "SELECT 1 FROM User WHERE User = ?;";
	sqlite3_stmt* stmt = nullptr;
	if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
	{
		std::cerr << "Problem occurred: " << sqlite3_errmsg(db.getDB()) << std::endl;
		return;
	}
	if (sqlite3_bind_text(stmt, 1, userID.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK)
	{
		std::cerr << "Binding issue occurred: " << sqlite3_errmsg(db.getDB()) << std::endl;
		sqlite3_finalize(stmt);
		return;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::cout << "User found in the database. " << std::endl;
	}
	else if (sqlite3_step(stmt) == SQLITE_DONE)
	{
		std::cout << "User not found in the database. " << std::endl;
	}
	else
	{
		std::cout << "Error checking user. " << std::endl;
	}
	sqlite3_finalize(stmt);
}
