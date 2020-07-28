#include "Transaction.h"

Transaction::Transaction(Account& s, Account& r, double amount)
{
	std::ostringstream m;
	m << "\nOperation: transfering money;\nSender: " << s.GetID()
		<< ";\nReceiver: " << r.GetID() << ";\nAmount: " << amount
		<< ";\nBalance: " << s.GetBalance();

	msg = m.str();
}

const string& Transaction::getMsg() const 
{ 
	return msg; 
};