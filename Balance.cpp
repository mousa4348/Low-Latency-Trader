#include <iostream>
#include "libraries.h"


void Balance::addToBalance(double AmtToAdd)
{
	balanceAmt += AmtToAdd;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Added $" << AmtToAdd << " to your account! Current Balance: $" << balanceAmt << "\n";

}

void Balance::SubtFromBalance(double AmtToSubt)
{
	if (balanceAmt >= AmtToSubt)
	{
		std::cout << std::fixed << std::setprecision(2);
		balanceAmt -= AmtToSubt;
		std::cout << "Removed $" << AmtToSubt << " from your account! Current Balance: $" << balanceAmt << "\n";
	}
	else
	{
		std::cout << "Not Enough Funds. Please add more to complete this transaction. \n";
		
	}
	
}
bool Balance::isEnough(double AmtToSubt)
{
	return AmtToSubt < balanceAmt;
}//Returns true if the price is less than the balance, false if higher than the balance

void Balance::display() const
{
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "\nCurrent Balance: $" << balanceAmt << "\n";
}