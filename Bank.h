#pragma once
#include "Account.h"
using namespace std;

class Bank
{
private:
	list<Account> users;
	void addUser(Account*); // +
	//void removeUser(long long int);
	Account* findUser(long long int); // +
	int getUsersN(); // +
	void display_users(); // +
	void save(Account*);
	void save();
	bool upload();

	void setTransactionData(Account*, double&);

	void services(Account&);
	Account* signIn(); // +

public:
	Bank(); // +
	~Bank(); // +
	void launch();
};
