#ifndef APIHANDLER_H
#define APIHANDLER_H
#include "libraries.h"
#include <string>

/*
 Class header file to handle API calls using cURL
*/
class APIHandler {
public:
	//Function declarations for each API call type
	std::string fetchPrice(const std::string& ticker);//Handles stock price information
	std::string fetchProfile(const std::string& ticker);//Handles invidual stock information
	std::string fetchSymbol(const std::string& ticker);//Handles stock symbol and identifiers
};

#endif //APIHANDLER_H

