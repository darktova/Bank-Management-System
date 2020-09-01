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
	Account* findUser(long long int, std::list<Account>::iterator&);
	int getUsersN(); // +
	void display_users(); // +
	void save(Account*);
	void save();
	bool upload();

	void setTransactionData(Account&, double&, std::list<Account>::iterator&);
	void services(Account&);
	Account* signIn(); // +

public:
	Bank(); // +
	~Bank(); // +
	void launch();
};
