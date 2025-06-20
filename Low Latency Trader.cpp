// Low Latency Trader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <imgui.h>
#include "WebSocketClient.h"
#include "libraries.h"

int main()
{
	/*
	Create the sqlite database, then create the tables.
	SQLite creates the tables locally and stores it within the machine.
	First execute creates the table.

	*/
	DatabaseManager db("Balance.db");
	db.execute("CREATE TABLE Balance( ID INT PRIMARY KEY, Amount REAL NOT NULL");

	auto ws = std::make_shared<WebSocketClient>();
	StockTrade trader;
	APIHandler api;
	std::unique_ptr<Balance> balance = std::make_unique<Balance>();
	std::string token = "d15dj29r01qhqto566ogd15dj29r01qhqto566p0";
	std::string url = "wss://ws.finnhub.io/?token=" + token;
	std::string input;
	int options;
	std::cout << "Welcome to Mousa'a Low Latency Trader! Please select one of the following options \n";
	std::cout << std::setw(90) << std::setfill('_') << "\n";
	std::cout << "| 1. Buy/Sell Stocks ";
	std::cout << "| 2. Check a stock ";
	std::cout << "| 3. Check balance/ Add to balance |\n";
	std::cout << "\nOption: ";
	std::cin >> options;

	//ESTABLISH CONNECTION VIA WEBSOCKET
	/*
	ws->setOnMessage([](const std::string& message)
		{
			std::cout << "Recieved: " << message;
		});

	ws->send("{\"type\"subscribe\",\"symbol\":\"AAPL\"}");

	std::thread websocketThread([ws, url]()
		{
			ws->connect(url);
			ws->run();
		});
	ws->send("{\"type\":\"subscribe\",\"symbol\":\"AAPL\"}");

	
	*/

	while (options != -1)
	{
		if (options == -1)
		{
			break;
		}
		std::cout << "NOTE: AT ANY POINT, TYPE '-1' IN ORDER TO EXIT\n\n";
		if (options == 1)
		{
			double balAmt = balance->getBalanceAmt();
			int quantity;
			if (balAmt <= 0)
			{
				std::cout << "This account lacks the funds to make purchases. Sell stocks or add money to your account. \n";
				return -1;
			}

			std::cout << "Welcome to the stock purchase and sell center! Would you like to buy or sell a stock? ";
			std::cin >> input;
			if (input == "Buy" || input == "buy")
			{
				balance->display();
				std::cout << "\n\nWelcome to the buy station! Enter the stock that you would like to purchase: ";
				std::cin >> input;
				std::cout << "Enter the amount you would like to purchase: ";
				std::cin >> quantity;
				
				trader.buy(input, quantity, balance);
				trader.display();
			}
			if (input == "Sell" || input == "sell")
			{
				balance->display();
				std::cout << "\n\nWelcome to the sell station! Enter the stock that you will sell: ";
				std::cin >> input;
				std::cout << "\nEnter the amount you would like to sell: ";
				std::cin >> quantity;

				trader.sell(input, quantity, balance);
				std::cout << "\n";
				trader.display();
			}
			if (input == "-1" || input == "2")
			{
				options = std::stoi(input);//Turn the input back to an integer, then assign it to option
				std::cout << "Exiting option.... \n";
			}
		}
		else if (options == 2)
		{
			std::cout << "Enter a stock symbol. It must be valid: ";
			std::cin >> input;
			std::string result = api.fetchPrice(input);
			std::string result2 = api.fetchProfile(input);
			

		}
		else if (options == 3)
		{
			double amt;
			std::cout << "Welcome to the balance center! Enter a dollar amount to add to your balance: ";
			std::cin >> amt;
			
			if (amt == -1)
				break;
			std::cout << "\n";
			balance->addToBalance(amt);
			db.execute("INSERT INTO Balance (Amount) VALUES (" + std::to_string(amt) + ");");
			//Inserts the amount entered into the query
			
		}
		else
		{
			std::cout << "Invalid option. Please enter a different option: ";
			std::cin >> options;
		}
		std::cout << "\nSelect a different option: ";
		std::cin >> options;
	}
	//websocketThread.join();
	 std::cout << "\n\n\n";
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


