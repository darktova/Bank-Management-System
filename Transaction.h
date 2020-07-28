#pragma once
#include "Account.h"

class Transaction
{
private:
	std::string msg;

public:
	Transaction();
	
	// Sender, reciever, amount
	Transaction(Account&, Account&, double);
	const string& getMsg() const;
};

