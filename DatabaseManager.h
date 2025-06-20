#pragma once
#include "libraries.h"
#include <sqlite3.h>

class DatabaseManager
{
private:
	sqlite3* db;
	std::string dbName;
public:
	DatabaseManager(const std::string& name);
	~DatabaseManager();
	bool execute(const std::string& sql)
};

