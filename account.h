#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <deque>
#include <cmath>
#include <list>
#include <forward_list>
using namespace std;

// maximum number of accounts in 1-one session
static const unsigned short MAX_PEOPLE = 1024;

// default value for private data members
static const string _NULL = "null";

// UI - user interface
static const char* menu =
	"\n\n\t*	*	*   \"Bank Management System\"    *	*	*"
	"\n\n\tChoose the operation:"
	"\n\n\'C\' = Create new account"
	"\n\n\'L\' = Sign in via account.txt"
	"\n\n\'R\' = Sign in via custom file"
	"\n\n\'S\' = Sign out with account.txt"
	"\n\n\'W\' = Sign out with custom file"
	"\n\n\'D\' = Display account"
	"\n\n\nCURRENT USER: "
	"\t";

class Account
{
private:
	// number of existing people
	static unsigned short exitst_users_;

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
	
	// set new value to account id
	void SetID(unsigned long long int);
	
	// set the file name by user input (account.txt, so on).
	void SetNewFileName();

	// checking data correction 
	bool CheckFullName(const string&);
	bool CheckBirthday(const string&);
	bool CheckAge(unsigned short);
	bool CheckTown(const string&);
	bool CheckPhoneNumber(const string&);
	bool CheckBalance(long double);

public:
	// default constructor
	Account();

	// default destructor
	~Account();

	// setters for private data members
	void SetName(const string&);
	void SetSurname(const string&);
	void SetAge(unsigned short);
	void SetBirthday(const string&);
	void SetHometown(const string&);
	void SetCurrentCity(const string&);
	void SetPhoneNumber(const string&);
	void SetBalance(long double);

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
	unsigned short GetExistUsersNumber() const;

	// create a new account by user input 
	void CreateNewAccount();

	// read an account from default file "account.txt".
	void Load();
	 
	// read an account from new file (from user input).
	void LoadWith();

	// writes a private data to the default file "account.txt".
	void Save();

	// writes a private data to the new file (from user input).
	void SaveAs();

	// serves all operations from account via menu, UI.
	void StartService();
};

// output the account private data members
ostream& operator<<(ostream&, Account&);

// All active users
static map<unsigned short, Account> users;
#endif //	_ACCOUNT_