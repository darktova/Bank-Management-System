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

void Bank::setTransactionData(Account& receiver, double& amount, std::list<Account>::iterator& rec_it)
{
	// Transaction info.
	// ID
	int id = 0;
	std::cout << "\nReciever (ID): ";
	std::cin.tie();
	std::cin.clear();
	std::cin >> id;
	
	// receiver
	Account* aim = findUser(id, rec_it);
	if (!aim || aim->GetID() == 0)
		return;
	receiver = *aim;

	// Amount
	std::cout << "\nAmount ($): ";
	std::cin.tie();
	std::cin.clear();
	std::cin >> amount;
}

void Bank::services(Account& u)
{
	while (true)
		switch (selectServ(u))
		{
		case 'T':
			makeTransaction(u);
			break;
		case 'U':
			u.toUp();
			system("pause");
			break;
		case 'D':
			std::cout << u;
			system("pause");
			break;
		case 'A':
			displayAll();
			break;
		case 'R':
			deleteUser(u);
			logOut();
			return;
		case 'E':
			logOut();
			return;
		}
}

Account* Bank::signIn()
{
	if (users.size() == 0)
	{
		std::cout << "\n*\t*\t*\tThere are no users yet.\nYou can create your own -->";
		system("pause");
		return nullptr;
	}

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

char Bank::selectServ(Account& u)
{
	system("cls");

	char s = ' ';
	std::cout << header << operations
		<< "\nBalance: " << u.GetBalance() << "$"
		<< "\nChoice: ";
	std::cin.tie();
	std::cin.clear();
	std::cin >> s;

	return toupper(s);
}

void Bank::logOut()
{
	system("cls");
	std::cout << header
		<< "\n\nLogging out from the Bank.";
	save();
	upload();
	system("pause");

}

void Bank::displayAll()
{
	display_users();
	system("pause");
}

void Bank::deleteUser(Account& u)
{
	removeUser(u.GetID());
}

void Bank::makeTransaction(Account& u)
{
	double amount = 0.0;
	Account* receiver = new Account();
	std::list<Account>::iterator rec_it;
	bool status = false;

	setTransactionData(*receiver, amount, rec_it);
	status = u.makeTransaction(*receiver, amount);

	if (status)
		replaceUser(receiver, rec_it);

	system("pause");
}

void Bank::launch()
{
	while (true)
	{
		Account* user = new Account();
		int status = user->logIn();

		switch (status)
		{
		case NULL:
			continue;
			break;
		case UNREGISTERED:
			addUser(user);
			break;
		case REGISTERED:
			user = signIn();
			break;
		}

		if (!user)
		{	
			std::cerr << "\nUser isn't extist.";
			continue;
		}

		services(*user);
	}
}

void Bank::addUser(Account* u)
{
	if (!u)
	{
		std::cerr << "Empty user!\n";
		return;
	}
	users.push_back(*u);
}

std::list<Account>::iterator Bank::removeUser(long long int id)
{
	std::list<Account>::iterator u_it;
	findUser(id, u_it);
	return users.erase(u_it);
}

void Bank::replaceUser(Account* u, std::list<Account>::iterator rec_it)
{
	std::list<Account>::iterator ins_it = users.erase(rec_it);
	users.insert(ins_it, *u);
}

Account* Bank::findUser(long long int id)
{
	for (auto i = users.begin(); i != users.end(); ++i)
		if (i->GetID() == id)
			return &(*i);

	return nullptr;
}

Account* Bank::findUser(long long int id, std::list<Account>::iterator& rec_it)
{
	rec_it = users.end();
	for (auto i = users.begin(); i != users.end(); ++i)
		if (i->GetID() == id)
		{
			rec_it = i;
			return &(*i);
		}

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