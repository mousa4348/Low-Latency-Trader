#pragma once
#ifndef STOCKTRADING_H
#define STOCKTRADING_H
#include "libraries.h"
#include "Balance.h"
#include <vector>
#include <string>
#include <unordered_map>

/*
 Class header file that handles the "stock exchange" portion of the program.
  Includes setters and getters, a buy and sell option, and a funcion to display owned stocks
*/
class StockTrade
{
private:
	int buyingPower;
	APIHandler api;
	std::unordered_map<std::string, int> stock;

public:
	//Constructors
	StockTrade() : buyingPower(0) {}; //An empty account
	StockTrade(int initBP) : buyingPower(initBP) {}; //An account with a set amount of buying power
	StockTrade(int initBP, const std::unordered_map<std::string, int>& initTrade) : buyingPower(initBP), stock(initTrade) {}; //An account with a set buying power and initial trade

	//Function declarations
	void setBP(int newBuyingPower) { buyingPower = newBuyingPower; }
	int getBP() { return buyingPower;  }
	void setStock(std::unordered_map<std::string, int> newStock) { stock = newStock; }
	void buy(const std::string& ticker, int quantity, std::unique_ptr<Balance>& balance);
	void sell(const std::string& ticker, int quantity, std::unique_ptr<Balance>& balance);
	void display() const;
	
};

#endif //STOCKTRADING_H