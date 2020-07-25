#pragma once
#include <string>

class Transaction
{
private:
	std::string msg;
	Transaction* next;

public:
	Transaction();
	Transaction(double);

};

