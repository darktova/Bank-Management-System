#pragma once
#include "Account.h"
using namespace std;

class Bank
{
private:
	// Account Interface
	list<Account> users;
	void addUser(Account*); 
	std::list<Account>::iterator removeUser(long long int); 
	void replaceUser(Account*, std::list<Account>::iterator); 
	Account* findUser(long long int); 
	Account* findUser(long long int, std::list<Account>::iterator&); 
	int getUsersN(); 

	Account* signIn(); 
	void setTransactionData(Account&, double&, std::list<Account>::iterator&); 
	void display_users(); 
	void save(Account*); 
	void save(); 
	bool upload();
	
	// Services
	void services(Account&);
	char selectServ(Account&); 
	void makeTransaction(Account&); 
	void displayAll(); 
	void deleteUser(Account&);
	void logOut();

public:
	// Constructor 
	Bank();
	
	// Destructor
	~Bank(); 

	// Main Bank function
	void launch();
};
