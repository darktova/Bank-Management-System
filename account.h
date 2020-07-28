#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <list>
#include <stack>
#include "Data.h"
#include "Transaction.h"
#include "Bank.h"
using namespace std;

class Account
{
private:
	std::stack<Transaction> history;

	// name where to write, read into, from file 
	static string reserve_file_name_;
	unsigned long long int id_;
	string name_;
	string surname_;
	unsigned short age_;
	string birthday_;
	string hometown_;
	string current_city_;
	string phone_number_;
	long double balance_;
	char *username_, *password_;
	
	// set new value to account id
	void SetID(unsigned long long int);
	
	// set the file name by user input (account.txt, so on).
	void setNewFileName();

	// checking data correction 
	bool CheckFullName(const string&);
	bool CheckBirthday(const string&);
	bool CheckAge(unsigned short);
	bool CheckTown(const string&);
	bool CheckPhoneNumber(const string&);
	bool CheckBalance(long double);

	// setters for private data members
	void SetName(const string&);
	void SetSurname(const string&);
	void SetAge(unsigned short);
	void SetBirthday(const string&);
	void SetHometown(const string&);
	void SetCurrentCity(const string&);
	void SetPhoneNumber(const string&);
	void SetBalance(long double);
	bool setUsername(char*);
	bool setPassword(char*);

	// create a new account by user input 
	bool createNewAccount();

	// read an account from default file "account.txt".
	bool load();

	// read an account from new file (from user input).
	bool loadWith();

	// Manual log in: login + password
	bool manualLoad();

	// writes a private data to the default file "account.txt".
	void save();

	// writes a private data to the new file (from user input).
	void saveAs();


	// default destructor
	~Account();
public:
	
	// default constructor
	Account();

	// getters for private data members 
	unsigned long long int GetID() const;
	const string& GetName() const;
	const string& GetSurname() const;
	unsigned short GetAge() const;
	const string& GetBirthday() const;
	const string& GetHometown() const;
	const string& GetCurrentCity() const;
	const string& GetPhoneNumber() const;
	long double GetBalance() const;

	// Sign in/Register account.
	bool logIn();

	// id, amount
	void makeTransaction(Account&, double);
	
	void toUp(); 
};

// output the account private data members
ostream& operator<<(ostream&, Account&);
#endif //	_ACCOUNT_