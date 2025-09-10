#pragma once
#include <iostream>
#include <string>
#include "libraries.h"

using std::string;
class Login {
private:
		
		string userID;
		string password;
		string firstName, lastName;

public:
	//Figure out what the fuck to do here
	Login(string NewuserID, string Newpassword) : userID(NewuserID), password(Newpassword) {};
	void createAccount(string userID, string password, string firstName, string lastName, DatabaseManager db);
	bool password_check(string password);
	bool password_change(const string& userID, string& password, string& newPassword, DatabaseManager& db);\
		string getUserID() { return userID; }
	void setUserID(string newUserID) { userID = newUserID; }
	string getPassword() { return password;  }
	void setPassword(string newPassword) { password = newPassword;  } 



};