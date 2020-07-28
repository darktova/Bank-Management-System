#include "Bank.h"

Bank::Bank()
{
}

int Bank::getUsersN()
{
	return users.size();
}

void Bank::services(Account& u)
{
	system("cls");
	cout << header << services << "\nChoice: ";
	char s;
	cin >> s;

	switch (toupper(s))
	{
	case 'T':
		// Transaction info.
		cout << "\nReciever (ID): ";
		int id;
		cin >> id;
		cout << "\nAmount ($): ";
		double amount;
		cin >> amount;

		// Find receiver
		Account* receiver;
		for (auto i = users.begin(); i != users.end(); ++i)
			if (i->GetID() == id)
				*receiver = *i;

		u.makeTransaction(*receiver, amount);
		break;
	case 'U':
		u.toUp();
		break;
	}
}

void Bank::Launch()
{
	Account* user = new Account();
	user->logIn();
	services(*user);

}
