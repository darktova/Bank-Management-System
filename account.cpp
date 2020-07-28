#include "Account.h"

Account::Account()
	: id_(NULL - 1), name_(_NULL), surname_(_NULL),
	birthday_(_NULL), hometown_(_NULL), current_city_(_NULL),
	phone_number_(_NULL), age_(NULL), balance_(NULL),
	username_(NULL), password_(NULL)
{
	SetID(getUsersN() + 5);
}

Account::~Account()
{
}

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
		curr_month = dur->tm_mon + 1;

	// checking for incorrect date num.
	bool incorrect_date =
		(!m || m > 12 || ((curr_month < m) && (age_ == curr_year - y)) ||
		((curr_month > m) && (age_ < curr_year - y)) ||
			!d || d > 31 ||
			y < 1970 || y > 2170);
	if (incorrect_date)
	{
		cerr << "Error: Incorrect numbers of date.\n";
		return false;
	}

	// success: correct birthday;
	return true;
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

void Account::SetBirthday(const string& s)
{
	if (CheckBirthday(s))
		birthday_ = s;
}

void Account::SetAge(unsigned short age)
{
	if (CheckAge(age) && (birthday_ != _NULL))
		age_ = age;
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

bool Account::setUsername(char* u)
{
	if (!u || strlen(u) < 4)
		return false;

	username_ = u;
	return true;
}

bool Account::setPassword(char* p)
{
	if (!p || strlen(p) < 8)
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

bool Account::createNewAccount()
{
	cout << "Starting processing the new account user.\n";
	
	string name;
	string surname;
	unsigned short age;
	string birthday;
	string hometown;
	string current_city;
	string phone_number;
	long double balance;
	char* usernameAttempt = new char[64];
	char* passwordAttempt = new char[64];

	SetID(rand() % 1024);
	cout << "Your ID is: " << GetID() << '\n';
	
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
	char *username = new char[64], 
		*password = new char[64];

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
	return 1;
}

bool Account::loadWith()
{
	setNewFileName();
	return load();
}

bool Account::manualLoad()
{
	cout << "\nUsername: ";
	char *usernameAttempt = 0;
	cin >> usernameAttempt;
	if (strcmp(usernameAttempt, username_) == 0)
	{
		cout << "\nPassword: ";
		char *passwordAttempt = 0;
		cin >> passwordAttempt;
		if (strcmp(passwordAttempt, password_) == 0)
		{
			cout << "\nLogin successful.";
			return true;
		}
	}
	return false;
}

void Account::save()
{
	cout << "Saving is running . . .\n";

	ofstream os(reserve_file_name_, ios::out | ios::binary);
	if (!os.is_open() || os.fail())
	{
		cerr << "Error: Read file " << reserve_file_name_ << '\n';
		return;
	}

	os << id_ << ' ' << name_ << ' ' 
		<< surname_ << ' ' << birthday_ << ' ' << hometown_ 
		<< ' ' <<current_city_ << ' ' << phone_number_ << ' '
		<< age_ << ' ' << setprecision(4) << balance_ 
		<< username_ << ' ' << password_;
	
	cout << "Saving has been finished successfully.\n";
}

void Account::saveAs()
{
	setNewFileName();
	save();
}

bool Account::logIn()
{
	bool i = 0;
	while (i == 0)
	{
		system("cls");
		cout << header << menu << id_ 
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
		default:
			i = manualLoad();
			break;
		}
	}
	
	system("cls");
	cout << "Login successful";
	
	return true;
}

void Account::makeTransaction(Account& receiver, double amount)
{
	cout << "\nMaking transaction ...";
	if (balance_ - amount < 0)
		cout << "\nFailure: Not enough money."
			<< "\nOperation: transfering " << amount << "$"
			<< "\nBalance: " << balance_;
	
	Transaction t(*this, receiver, amount),
		t2(receiver, *this, -amount);
	SetBalance(balance_ - amount);
	receiver.balance_ += amount;
	history.push(t);
	receiver.history.push(t2);
}

void Account::toUp()
{
	// source;
	double amount;
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