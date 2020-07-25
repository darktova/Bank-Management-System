#include "Transaction.h"

Transaction::Transaction()
	: msg(NULL), next(new Transaction()) {}

Transaction::Transaction(double amount)
	: msg(NULL), next(new Transaction()) {}