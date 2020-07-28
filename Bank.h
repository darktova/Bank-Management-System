#pragma once
#include "Account.h"

class Bank
{
private:
	int getUsersN();
	list<Account> users;
	void services(Account&);

public:
	Bank();
	void Launch();

};
