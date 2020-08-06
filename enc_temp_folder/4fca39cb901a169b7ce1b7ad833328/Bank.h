#pragma once
#include "Account.h"
using namespace std;

class Bank
{
private:
	Account* admin;
	list<Account*> users;

	void services(Account&);
	int getUsersN();
	void save(Account*);
	void save();
	bool upload();

public:
	Bank();
	~Bank();
	void launch();
	void addUser(Account*);
};
