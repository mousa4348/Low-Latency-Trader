#include "login.h"
#include "libraries.h"

void createAccount(string userID, string password, string firstName, string lastName, DatabaseManager db)
{

	db.execute("INSERT INTO User(UserID, Password, firstName, lastName) VALUES ("
		+ userID + ", " + password + ", " + firstName + ", " + lastName + ");");	
}

bool password_checker(string password)
{
	bool isDigit = false, isUpper = false, isLower = false, hasSpecial = false;
	int password_strength = 0;

	if (password.empty())
	{
		std::cerr << "Password is empty and therefore invalid. ";
		return false;
	}

	if (password.length() >= 8)
	{
		password_strength += 2;
	}
	if (password.length() < 8)
	{
		password_strength++;
	}
	for (char c : password)
	{
		if (std::isupper(c))
			password_strength += 2;
		isUpper = true;
		if (std::islower(c))
			password_strength += 2;
		isLower = true;
		if (std::isdigit(c))
			password_strength += 3;
		isDigit = true;
		if (!std::isalnum(c) && !std::isspace(c))
			password_strength += 2; //Special characters: if not a letter, number, or whitespace, then it must be spcial
		hasSpecial = true;
	}
	if (isUpper && isLower && isDigit && hasSpecial)
	{
		std::cout << "There are enough differing symbols. ";
	}
	if (password_strength < 9)
	{
		std::cout << "Your password is too short. ";
	}
	else if (password_strength >= 9)
	{
		std::cout << "Your password is strong! ";
		return true;
	}
	return false;
}
bool password_change(const string& userID, string& password, string& newPassword, DatabaseManager& db)
{
	string res = "SELECT Password FROM User WHERE userID = " + userID;//Find the actual password of the user
	string currentPass;
	auto callback = [](void* data, int argc, char** argv, char** arColName) -> int
		{
			if (argc > 0 && argv[0] != nullptr)
			{
				std::string* pwd = static_cast<std::string*>(data);
				*pwd = argv[0];
			}
			return 0;
		};

	char* errMsg = nullptr;
	int rc = sqlite3_exec(db.getDB(), res.c_str(), callback, &currentPass, &errMsg);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Error fetching password: " << errMsg << std::endl; //Something went wrong
		sqlite3_free(errMsg);
	}


	if (currentPass == password)
	{
		std::cout << "Similar password. Please try again: " << std::endl;
		return false;
		//If password is the same as the one existing.
	}
	string updatePass = "UPDATE User SET Password = '" + newPassword + "' WHERE UserID = '" + userID + "';";
	if (!db.execute(updatePass))
	{
		std::cerr << "Error executing password upate." << std::endl;
		return false;
	}//Updating the database failed.
	std::cout << "Password changed! " << std::endl;
	return true;//Otherwise, everything worked! Probably.
}