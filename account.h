#pragma once
#include "Constants.h"

class Account
{
	unsigned long long int id_;
	string name_;
	string surname_;
	unsigned short age_;
	string birthday_;
	string hometown_;
	string current_city_;
	string phone_number_;
	long double balance_;
	string username_;
	string password_;

	// checking data correction +
	bool CheckFullName(const string&);
	bool CheckAge(unsigned short);
	bool CheckBirthday(const string&);
	bool CheckTown(const string&);
	bool CheckPhoneNumber(const string&);
	bool CheckBalance(long double);
	bool checkToUpAmount(double&);

	void signOut();

public:

	// default constructor +
	Account();

	// setters for private data members +
	// set new value to account id 
	void SetID(unsigned long long int);
	bool SetName(const string&);
	bool SetSurname(const string&);
	bool SetAge(unsigned short);
	bool SetBirthday(const string&);
	bool SetHometown(const string&);
	bool SetCurrentCity(const string&);
	bool SetPhoneNumber(const string&);
	bool SetBalance(long double);
	bool setUsername(const string&);
	bool setPassword(const string&);

	// getters for private data members +
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

	// create a new account by user input 
	bool createNewAccount();

	// Sign in/Register account.
	int logIn();

	// id, amount
	bool makeTransaction(Account&, double);
	
	void toUp();
};

// output the account private data members
std::ostream& operator<<(std::ostream&, Account&);
ofstream& operator<<(ofstream&, Account&);
ifstream& operator>>(ifstream&, Account&);