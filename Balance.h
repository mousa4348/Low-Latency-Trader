#pragma once
#ifndef BALANCE_H
#define BALANCE_H
/*
 Class header file to get, set, add and subtract a balance from a user's account.
*/

#include <iostream>
#include "libraries.h"

class Balance
{
private:
	double balanceAmt;

public:
	//Two constructors, the first is in the event that the user has no balance
	Balance() : balanceAmt(0.0) {};
	Balance(double initBalance) : balanceAmt(initBalance) {};

	void setBalanceAmt(double newBalance) { balanceAmt = newBalance; }
	double getBalanceAmt() { return balanceAmt; }
	void addToBalance(double AmtToAdd);
	bool isEnough(double AmtToSubt);
	void SubtFromBalance(double AmtToSubt);
	void display() const;

};

#endif //BALANCE_H
