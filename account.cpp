#include "Account.h"
#include "Bank.h"
using namespace std;

Account::Account()
	: id_(NULL - 1), name_(_NULL), surname_(_NULL),
	birthday_(_NULL), hometown_(_NULL), current_city_(_NULL),
	phone_number_(_NULL), age_(NULL), balance_(NULL),
	username_(_NULL), password_(_NULL)
{}

void Account::setNewFileName()
{
	cout << "Setting new file name is running . . .\n"
		<< "Enter a file name: ";

	// new cin input
	cin.sync(); 
	cin.clear();

	// checking for cin incorrect work
	if (cin.fail())
	{
		cerr << "Error: cin has been failed.\n";
		return;
	}


	// a new file name
	string s;
	cin >> s;

	// checking for incorrect file name
	if (s.empty())
	{
		cerr << "Error: new file name is incorrect.\n";
		return;
	}

	reserve_file_name_ = s;

	cout << "Setting new file name has been finished successfully.\n";
}

bool Account::CheckFullName(const string& s)
{
	size_t len = s.size();
	if (len == 0 || len > 50)
	{
		cerr << "Error: Incorrect name length.\n";
		return false;
	}

	for (unsigned i = 0; i < len; ++i)
		if (!isalpha(s[i]))
		{
			cerr << "Error: Incorrect name contents.\n";
			return false;
		}

	return true;
}

bool Account::CheckAge(unsigned short age)
{
	if (age < 0 || age > 150)
	{
		cerr << "Error: age borders has been broken.\n";
		return false;
	}

	return true;
}

bool Account::CheckBirthday(const string& s)
{
	// checking for incorrect length
	if (s.size() != 10)
	{
		cerr << "Error: Incorrect birthday length.\n";
		return false;
	}

	// checking for format (01.16.2020)
	bool incorrect_format =
		!(isdigit(s[0]) && isdigit(s[1]) && s[2] == '.' &&
			isdigit(s[3]) && isdigit(s[4]) && s[5] == '.' &&
			isdigit(s[6]) && isdigit(s[7]) && isdigit(s[8]) && isdigit(s[9]));
	
	if (incorrect_format)
	{
		cerr << "Error: Incorrect birthday format or unavailable chars.\n";
		return false;
	}

	// transform date to nums.
	char mm[2] = { s[0], s[1] },
		dd[2] = { s[3], s[4] },
		yyyy[4] = { s[6], s[7], s[8], s[9] };

	int m = atoi(mm),
		d = atoi(dd),
		y = atoi(yyyy);

	struct tm* dur; // Pointer to struct tm.
	time_t sec; // For seconds.
	time(&sec); // Get the present time.
	dur = localtime(&sec);
	int curr_year = dur->tm_year + 1900,
		curr_month = dur->tm_mon + 1,
		curr_day = dur->tm_mday;

	bool correct_date = ((y < curr_year) && (m && m < 12) && (d && d < 31)
		&& (((curr_year - y == age_) && (m < curr_month))
			|| ((curr_year - y == age_ + 1) && (m > curr_month))
			|| ((curr_year - y == age_) && (m == curr_month) && (d >= curr_day))));

	return (correct_date);
}

bool Account::CheckTown(const string& s)
{
	// checking for length
	if (s.empty() || s.length() > 50)
	{
		cerr << "Error: Incorrect hometown length.\n";
		return false;
	}

	// checking for all letters
	for (unsigned i = 0, len = s.size(); i < len; ++i)
		if (!isalpha(s[i]))
		{
			cerr << "Error: hometown has incorrect contents.\n";
			return false;
		}

	return true;
}

bool Account::CheckPhoneNumber(const string& s)
{
	// checking for correct size and starting from '+'
	if (s.size() != 13 || s[0] != '+')
	{
		cerr << "Error: Incorrect phone number length "
			<< "or starts no with \'+\'.\n";
		return false;
	}

	// checking for unavailable chars.
	for (unsigned i = 1; i < 13; ++i)
		if (!isdigit(s[i]))
		{
			cerr << "Error: Phone number has no digit.\n";
			return false;
		}

	return true;
}

bool Account::CheckBalance(long double b)
{
	if (b < 0 || b > 10e10)
	{
		cerr << "Error: balance borders has been broken.\n";
		return false;
	}

	return true;
}

void Account::SetID(unsigned long long int id)
{
	id_ = id;
}

void Account::SetName(const string& s)
{
	if (CheckFullName(s))
		name_ = s;
}

void Account::SetSurname(const string& s)
{
	if (CheckFullName(s))
		surname_ = s;
}

void Account::SetAge(unsigned short age)
{
	if (CheckAge(age))
		age_ = age;
}

void Account::SetBirthday(const string& s)
{
	if (CheckBirthday(s))
		birthday_ = s;
}

void Account::SetHometown(const string& s)
{
	if (CheckTown(s))
		hometown_ = s;
}

void Account::SetCurrentCity(const string& s)
{
	if (CheckTown(s))
		current_city_ = s;
}

void Account::SetPhoneNumber(const string& s)
{
	if (CheckPhoneNumber(s))
		phone_number_ = s;
}

void Account::SetBalance(long double balance)
{
	if (CheckBalance(balance))
		balance_ = balance;
}

bool Account::setUsername(const string& u)
{
	if (!u.size() || u.size() > 10)
		return false;

	username_ = u;
	return true;
}

bool Account::setPassword(const string& p)
{
	if (!p.size() || p.size() > 8)
		return false;

	password_ = p;
	return true;
}

unsigned long long int Account::GetID() const { return id_; }

const string& Account::GetName() const { return name_; }

const string& Account::GetSurname() const { return surname_; }

const string& Account::GetBirthday() const { return birthday_; }

unsigned short Account::GetAge() const { return age_; }

const string& Account::GetHometown() const { return hometown_; }

const string& Account::GetCurrentCity() const { return current_city_; }

const string& Account::GetPhoneNumber() const { return phone_number_; }

long double Account::GetBalance() const { return balance_; }

const string& Account::GetUsername() const { return username_; }

const string& Account::GetPassword() const { return password_; }

bool Account::createNewAccount()
{
	cout << "Starting processing the new account user.\n";
	
	string name = "";
	string surname = "";
	unsigned short age = 0;
	string birthday = "";
	string hometown = "";
	string current_city = "";
	string phone_number = "";
	long double balance = 0.0;
	string usernameAttempt = "";
	string passwordAttempt = "";

	time(0);
	SetID(rand() % 1024);
	cout << "Your ID is: " << id_ << '\n';
	
	cout << "First name: ";
	cin >> name;
	SetName(name);
	
	cout << "Second name: ";
	cin >> surname;
	SetSurname(surname);
	
	cout << "Age: ";
	cin >> age;
	SetAge(age);
	
	cout << "Birthday, format mm.dd.yyyy: ";
	cin >> birthday;
	SetBirthday(birthday);
	
	cout << "Hometown: ";
	cin >> hometown;
	SetHometown(hometown);
	
	cout << "Current city: ";
	cin >> current_city;
	SetCurrentCity(current_city);
	
	cout << "Phone number, format +380XXXXXXXXX: ";
	cin >> phone_number;
	SetPhoneNumber(phone_number);

	cout << "Current balance: ";
	cin >> balance;
	SetBalance(balance);

	cout << "\nUsername: ";
	cin >> usernameAttempt;
	cout << "\nPassword: ";
	cin >> passwordAttempt;
	if (!setUsername(usernameAttempt) 
		|| !setPassword(passwordAttempt))
		return false;

	cout << "Processing the new account user is finished successfully.\n";
	return true;
}

bool Account::load()
{
	ifstream is(reserve_file_name_, ios::in | ios::binary);
	if (!is.is_open() || is.fail())
	{
		cerr << "Error: loading with file "
			<< reserve_file_name_ << " has been failed\n";
		return false;
	}

	cout << "Loading is running . . .\n";

	unsigned long long int id;
	string name;
	string surname;
	unsigned short age;
	string birthday;
	string hometown;
	string current_city;
	string phone_number;
	long double balance;
	string username;
	string password;

	is >> id >> name
		>> surname >> age >> birthday
		>> hometown >> current_city
		>> phone_number >> balance 
		>> username >> password;

	SetID(id);
	SetName(name);
	SetSurname(surname);
	SetAge(age);
	SetBirthday(birthday);
	SetHometown(hometown);
	SetCurrentCity(current_city);
	SetPhoneNumber(phone_number);
	SetBalance(balance);
	setUsername(username);
	setPassword(password);

	cout << "Loading has been finished successfully.\n";
	return true;
}

bool Account::loadWith()
{
	setNewFileName();
	return load();
}

bool Account::manualLoad()
{
	time(0);
	SetID(rand() % 1024);

	if (username_.size())
	{
		std::cout << "You are not registered yet!\n";
		system("pause");
		return false;
	}

	cout << "\nUsername: ";
	string usernameAttempt = "";
	cin >> usernameAttempt;
	if (usernameAttempt.compare(username_) == 0)
	{
		cout << "\nPassword: ";
		string passwordAttempt = "";
		cin >> passwordAttempt;
		
		if (passwordAttempt.compare(password_) == 0)
		{
			cout << "\nLogin successful.";
			return true;
		}
	}
	return false;
}

bool Account::logIn()
{
	bool i = 0;
	while (i == 0)
	{
		system("cls");
		cout << header << menu 
			<< "\n\nChoice: ";
		char operation;
		cin >> operation;

		switch (toupper(operation))
		{
		case 'C':
			i = createNewAccount();
			break;
		case 'L':
			i = load();
			break;
		case 'R':
			i = loadWith();
			break;
		case 'M':
			i = manualLoad();
			break;
		case 'E':
			system("cls");
			std::cout << header
				<< "\n\nLogging out from the Bank.";
			system("pause");
			exit(0);
		}
	}

	cout << "Login successful";
	
	return true;
}

void Account::makeTransaction(Account* receiver, double amount)
{
	if (id_ == receiver->id_)
	{
		std::cout << "\nError: Incorrect transaction receiver.";
		system("pause");
		return;
	}

	cout << "\nMaking transaction ...";

	// Cheking
	if (balance_ - amount < 0)
		cout << "\nFailure: Not enough money."
			<< "\nOperation: transfering " << amount << "$"
			<< "\nBalance: " << balance_;

	// Transaction history
	std::ostringstream msg;
	msg << "\nOperation: transfering money;\nSender: " << id_
		<< ";\nReceiver: " << receiver->GetID() << ";\nAmount: " << amount
		<< ";\nBalance: " << balance_;
	// history.push_back(msg.str());

	// Transfering money
	SetBalance(balance_ - amount);
	receiver->balance_ += amount;
}

void Account::toUp()
{
	// source;
	double amount = 0.0;
}

ostream& operator<<(ostream& os, Account& acc)
{
	if (os.fail())
	{
		cerr << "Error: Outputting account data from ostream failed.\n";
		return os;
	}

	cout << "Outputting is running . . .\n";

	os << "Id:\t" << acc.GetID()
		<< "\nFirst name:\t" << acc.GetName()
		<< "\nSurname:\t" << acc.GetSurname()
		<< "\nBirthday:\t" << acc.GetBirthday()
		<< "\nHometown:\t" << acc.GetHometown()
		<< "\nCurrent city:\t" << acc.GetCurrentCity()
		<< "\nPhone number:\t" << acc.GetPhoneNumber()
		<< "\nAge:\t" << acc.GetAge()
		<< "\nBalance:\t" << fixed << setprecision(4) << acc.GetBalance()
		<< '\n';

	cout << "Outputting has been finished successfully.\n";
	
	return os;
}

string Account::reserve_file_name_ = "account.txt";