#include "Bank.h"

Bank::Bank()
	: admin(new Account())
{
	upload();
}

Bank::~Bank()
{
	save();
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

	os << u->GetID() << ' ' << u->GetName() << ' '
		<< u->GetSurname() << ' ' << u->GetBirthday();
	os << ' ' << u->GetAge()
		<< ' ' << u->GetHometown() << ' ' << u->GetCurrentCity() << ' ';
	os << u->GetPhoneNumber() << ' ';
	os << ' ' << setprecision(4) << u->GetBalance()
		<< ' ' << u->GetUsername() << ' ' << u->GetPassword();

	cout << "Saving has been finished successfully.\n";
}

void Bank::save()
{
	for (; !users.empty(); users.pop_front())
		save(users.front());
}

bool Bank::upload()
{
	ifstream is("users.txt", ios::in);
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
		delete u;
	}

	cout << "Loading has been finished successfully.\n";
	return true;
}

int Bank::getUsersN()
{
	return users.size();
}

void Bank::services(Account& u)
{
	while (true)
	{
		system("cls");
		cout << header << operations 
			<< "\nBalance: " << u.GetBalance() << "$"
			<< "\nChoice: ";
		char s;
		int id;
		double amount;
		Account* receiver = new Account();

		cin >> s;

		switch (toupper(s))
		{
		case 'T':
			// Transaction info.
			cout << "\nReciever (ID): ";
			
			cin >> id;
			cout << "\nAmount ($): ";
			cin >> amount;

			// Find receiver
			for (auto i = *(users.begin()); i != *(users.end()); ++i)
				if (i->GetID() == id)
					receiver = i;
		
			if (!receiver)
			{
				cout << "There is no user with ID: " << id;
				system("pause");
				break;
			}
			u.makeTransaction(*receiver, amount);
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
	
	if (user->logIn() == 2)
	{
		std::cout << "\n\nLogging out from the Bank.";
		exit(0);
	}

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
	users.push_back(u);
}
