#include <map>
#include "Bank.h"

Bank::Bank()
{
	upload();
}

Bank::~Bank()
{
	save();
}

int Bank::getUsersN()
{
	return users.size();
}

void Bank::save(Account* u)
{
	cout << "Saving is running . . .\n";

	fstream os("users.txt", ios::out | ios::app | ios::ate);
	if (!os.is_open() || os.fail())
	{
		cerr << "Error: Read file " << "users.txt" << '\n';
		return;
	}

	os << u;

	cout << "Saving has been finished successfully.\n";
}

void Bank::save()
{
	for (; !users.empty(); users.pop_front())
		save(&(users.front()));
}

bool Bank::upload()
{
	ifstream is("users.txt", ios::in | ios::binary);
	if (!is.is_open() || is.fail() || !is || is.eof())
	{
		cerr << "Error: loading with file "
			<< "users.txt" << " has been failed\n";
		return false;
	}

	Account* u = new Account();
	std::map<long long int, Account*> filtered_users;

	while (!is.eof())
	{
		is >> *u;
		filtered_users.insert(pair<long long int, Account*>(u->GetID(), u));
	}

	for (auto i = filtered_users.begin(); i != filtered_users.end(); ++i)
		addUser(&(*i->second));
	filtered_users.clear();

	cout << "Loading has been finished successfully.\n";
	return true;
}

void Bank::setTransactionData(Account* r, double& amount)
{
	// Transaction info.
	int id = 0;
	cout << "\nReciever (ID): ";
	cin >> id;
	r = findUser(id);

	if (!r || r->GetID() == NULL)
	{
		cout << "There is no user with ID: " << id;
		system("pause");
		return;
	}

	cout << "\nAmount ($): ";
	cin >> amount;
}

void Bank::services(Account& u)
{
	while (true)
	{
		system("cls");
		char s = ' ';
		cout << header << operations 
			<< "\nBalance: " << u.GetBalance() << "$"
			<< "\nChoice: ";
		cin >> s;

		double amount = 0.0;
		Account* receiver = new Account();

		switch (toupper(s))
		{
		case 'T':
			setTransactionData(receiver, amount);
			u.makeTransaction(receiver, amount);
			break;
		case 'U':
			u.toUp();
			break;
		case 'D':
			std::cout << u;
			system("pause");
			break;
		case 'E':
			system("cls");
			std::cout << header
				<< "\n\nLogging out from the Bank.";
			save();
			upload();
			system("pause");
			return;
		}
	}
}

void Bank::launch()
{
	while (true)
	{
		Account* user = new Account();
		user->logIn();
		addUser(user);
		services(*user);
	}
}

void Bank::addUser(Account* u)
{
	if (!u)
	{
		cout << "Empty user!\n";
		return;
	}
	users.push_back(*u);
}

/*void Bank::removeUser(long long int id)
{
	users.remove(*findUser(id));
}*/

Account* Bank::findUser(long long int id)
{
	Account* r = new Account();
	r->SetID(NULL);
	for (auto i = users.begin(); i != users.end(); ++i)
		if (i->GetID() == id)
		{
			*r = *i;
			break;
		}

	return r;
}
