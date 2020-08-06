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

	ofstream os("users.txt", ios::out);
	if (!os.is_open() || os.fail())
	{
		cerr << "Error: Read file " << "users.txt" << '\n';
		return;
	}

	os << u->GetID() << ' ' << u->GetName() << ' ' << u->GetSurname() 
		<< ' ' << u->GetAge() << ' ' << u->GetBirthday()
		<< ' ' << u->GetHometown() << ' ' << u->GetCurrentCity() << ' '
		<< ' ' << u->GetPhoneNumber() << ' '
		<< ' ' << setprecision(4) << u->GetBalance()
		<< ' ' << u->GetUsername() << ' ' << u->GetPassword();

	cout << "Saving has been finished successfully.\n";
}

void Bank::save()
{
	for (; !users.empty(); users.pop_front())
		save(&(users.front()));
}

bool Bank::upload()
{
	ifstream is("users.txt", ios::in);
	is.seekg(ios::beg);
	if (!is.is_open() || is.fail() || !is || is.eof())
	{
		cerr << "Error: loading with file "
			<< "users.txt" << " has been failed\n";
		return false;
	}

	cout << "Loading is running . . .\n";

	unsigned long long int id = 0;
	string name = _NULL;
	string surname = _NULL;
	unsigned short age = 0;
	string birthday = _NULL;
	string hometown = _NULL;
	string current_city = _NULL;
	string phone_number = _NULL;
	long double balance = 0.0;
	char* username = new char[64]{ ' ' },
		* password = new char[64]{ ' ' };

	while (!is.eof())
	{
		is >> id >> name
			>> surname >> age >> birthday
			>> hometown >> current_city
			>> phone_number >> balance
			>> username >> password;

		Account* u = new Account();

		u->SetID(id);
		u->SetName(name);
		u->SetSurname(surname);
		u->SetAge(age);
		u->SetBirthday(birthday);
		u->SetHometown(hometown);
		u->SetCurrentCity(current_city);
		u->SetPhoneNumber(phone_number);
		u->SetBalance(balance);
		u->setUsername(username);
		u->setPassword(password);

		addUser(u);
	}

	cout << "Loading has been finished successfully.\n";
	return true;
}

void Bank::setTransactionData(Account* r, double& amount)
{
	r = nullptr;

	// Transaction info.
	int id = 0;
	cout << "\nReciever (ID): ";
	cin >> id;
	r = findUser(id);

	if (r == nullptr || !r->GetID())
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
		case 'E':
			system("cls");
			std::cout << header
				<< "\n\nLogging out from the Bank.";
			save();
			system("pause");
			exit(0);
		}
	}
}

void Bank::launch()
{
	Account* user = new Account();
	user->logIn();
	addUser(user);
	services(*user);
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
	for (auto i = users.begin(); i != users.end(); ++i)
		if (i->GetID() == id)
		{
			*r = *i;
			break;
		}

	return r;
}
