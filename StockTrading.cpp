#include <iostream>
#include "libraries.h"
#include "Balance.h"

void StockTrade::buy(const std::string& ticker, int quantity, std::unique_ptr<Balance>& balance)
{

	std::string strPrice = api.fetchPrice(ticker);
	if (strPrice.empty())
	{
		std::cout << "Result is empty. Try again!\n ";
		return;
	}

	double price = std::stod(strPrice);
	double BalAmt = balance->getBalanceAmt();

	double originalPrice = price;//Use this to keep the original price to display
	
	price *= quantity;
	if (!balance->isEnough(price))
	{
		std::cout << "Not enough funds. Add to your balance and try again. \n";
		return;
	}
	balance->SubtFromBalance(price);
	stock[ticker] += quantity; //Add purchased amount

	
	std::cout << "\n\nBought " << quantity << " Shares of " << ticker << " at " << originalPrice << "!\n";
	balance->display();
}

void StockTrade::sell(const std::string& ticker, int quantity, std::unique_ptr<Balance>& balance)
{
	std::string strPrice = api.fetchPrice(ticker);
	if (strPrice.empty())
	{
		std::cout << "Result is empty. Try again!\n ";
		return;
	}

	double price = std::stod(strPrice);
	double BalAmt = balance->getBalanceAmt();

	if (stock[ticker] >= quantity)
	{
		double originalPrice = price;
		stock[ticker] -= quantity; //Sell amount assuming there are enough stocks of a certain ticker to sell
		price *= quantity;//This becomes the amount to subtract
		balance->addToBalance(price);
		stock[ticker] -= quantity; //Sell amount assuming there are enough stocks of a certain ticker to sell
		
	}
	
	balance->display();

}

double StockTrade::current_price(const std::string& ticker)
{
	std::string strPrice = api.fetchPrice(ticker);
	if (strPrice.empty())
	{
		std::cout << "Reusult is empty. Try again!\n";
		return 0;
	}
	double price = std::stod(strPrice);
	return price;
}

void StockTrade::display() const
{
	std::cout << "\nCurrent shares: \n";
	for (const auto& [ticker, quantity] : stock)
	{
		std::cout << "\n- " << ticker << ": " << quantity << " Shares. \n";
	}
}