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
	std::string db_name = "users.txt";
	std::ios::openmode db_flags= ios::out | ios::app;
	ofstream os(db_name, db_flags);
	os << *u;
}

void Bank::save()
{
	// Erasing duplicates in the file
	ofstream os("users.txt", ios::out | ios::trunc);
	os << ' ';
	os.close();
	for (; !users.empty(); users.pop_front())
		save(&(users.front()));
}

bool Bank::upload()
{
	std::map<long long int, Account*> filtered_users;
	ifstream is("users.txt", ios::in | ios::binary);

	while (true)
	{
		if (!is.good())
			break;

		Account* u = new Account();
		is >> *u;
		
		if (u->GetID() == 0)
		{
			std::cout << "\nError: Empty user";
			continue;
		}
		filtered_users.insert(pair<long long int, Account*>(u->GetID(), u));
	}
			
	for (auto i = filtered_users.begin(); i != filtered_users.end(); ++i)
		addUser(&(*i->second));
	filtered_users.clear();

#ifdef _DEBUG_
	std::cout << "\nLoading has been finished successfully.";
	system("pause");
#endif // _DEBUG_

	return true;
}

void Bank::setTransactionData(Account* receiver, double& amount)
{
	// Transaction info.
	int id = 0;
	std::cout << "\nReciever (ID): ";
	std::cin >> id;
	receiver = findUser(id);

	if (receiver->GetID() == NULL)
	{
		std::cout << "There is no user with ID: " << id;
		system("pause");
		return;
	}

	std::cout << "\nAmount ($): ";
	std::cin >> amount;
}

void Bank::services(Account& u)
{
	while (true)
	{
		system("cls");
		char s = ' ';
		std::cout << header << operations 
			<< "\nBalance: " << u.GetBalance() << "$"
			<< "\nChoice: ";
		std::cin >> s;

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
			break;
		case 'A':
			display_users();
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
		system("pause");
	}
}

Account* Bank::signIn()
{
	system("cls");
	display_users();
	
	std::cout << "\nChoose your account: ";
	long long int id;
	std::cin >> id;
	Account* u = findUser(id);

	if (!u)
	{
		std::cout << "\nUser isn't exist.";
		return nullptr;
	}

	std::string username, password;
	std::cout << "\nUsername: ";
	std::cin >> username;
	if (username.compare(u->GetUsername()) == 0)
	{
		std::cout << "\nPassword: ";
		std::cin >> password;
		if (password.compare(u->GetPassword()) == 0)
		{
			std::cout << "\nSign in successfull.";
			return u;
		}
	}

	return nullptr;
}

void Bank::launch()
{
	while (true)
	{
		Account* user = new Account();
		int status = user->logIn();
		
		if (status == UNREGISTERED)
			addUser(user);
		else if (status == REGISTERED)
			user = signIn();

		if (user)
			services(*user);	
	
		std::cout << "\nUser isn't extist.";
	}
}

void Bank::addUser(Account* u)
{
	if (!u)
	{
		std::cout << "Empty user!\n";
		return;
	}
	users.push_back(*u);
}

//void Bank::removeUser(long long int){}

Account* Bank::findUser(long long int id)
{
	for (auto i = users.begin(); i != users.end(); ++i)
		if (i->GetID() == id)
			return &(*i);

	return nullptr;
}

void Bank::display_users()
{
	std::cout << "\n*\t*\t*\tUsers\t*\t*\t*"
		<< "\n#ID";
	int k = 0;
	for (auto i = users.begin(), j = users.end(); i != j; ++k, ++i)
		std::cout << "\n#" << k << ' ' << i->GetID();
}