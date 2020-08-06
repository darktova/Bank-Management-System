#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <list>
#include <stack>
#include "Data.h"
using namespace std;

class Account
{
private:
	
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
	
	// set the file name by user input (account.txt, so on).
	void setNewFileName();

	// checking data correction 
	bool CheckFullName(const string&);
	bool CheckAge(unsigned short);
	bool CheckBirthday(const string&);
	bool CheckTown(const string&);
	bool CheckPhoneNumber(const string&);
	bool CheckBalance(long double);

	// create a new account by user input 
	bool createNewAccount();

	// loading from account.txt
	bool load();

	// Manual log in: login + password
	bool manualLoad();

	// saving into "account.txt".
	void save();

	// saving into the new file (from user input).
	void saveAs();

public:

	// default constructor
	Account();

	// setters for private data members
	// set new value to account id
	void SetID(unsigned long long int);
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
	const string& GetUsername() const;
	const string& GetPassword() const;

	// read an account from new file (from user input).
	bool loadWith();

	// Sign in/Register account.
	bool logIn();

	// id, amount
	void makeTransaction(Account*, double);
	
	void toUp(); 
};

// output the account private data members
ostream& operator<<(ostream&, Account&);