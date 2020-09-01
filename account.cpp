#include "Account.h"
#include "Bank.h"
using namespace std;

Account::Account()
	: id_(NULL), name_(_NULL), surname_(_NULL),
	birthday_(_NULL), hometown_(_NULL), current_city_(_NULL),
	phone_number_(_NULL), age_(NULL), balance_(NULL),
	username_(_NULL), password_(_NULL)
{}

void Account::setNewFileName()
{
#ifdef _DEBUG_
	std::cout << "Setting new file name is running . . .\n";
#endif // _DEBUG_

	std::cout << "Enter a file name: ";
	std::cin.sync(); 
	std::cin.clear();

	// checking for std::cin incorrect work
	if (std::cin.fail())
	{
		cerr << "Error: std::cin has been failed.\n";
		return;
	}

	// a new file name
	string s;
	std::cin >> s;

	// checking for incorrect file name
	if (s.empty())
	{
		cerr << "Error: new file name is incorrect.\n";
		return;
	}

	reserve_file_name_ = s;

#ifdef _DEBUG_
	std::cout << "Setting new file name has been finished successfully.\n";
#endif // _DEBUG_
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
	#ifdef _DEBUG_
		std::cout << "Starting processing the new account user.\n";
	#endif // _DEBUG_
	
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

	srand((unsigned)time(0));
	SetID(rand() % 1024);
	std::cout << "Your ID is: " << id_ << '\n';
	
	std::cout << "First name: ";
	std::cin >> name;
	SetName(name);
	
	std::cout << "Second name: ";
	std::cin >> surname;
	SetSurname(surname);
	
	std::cout << "Age: ";
	std::cin >> age;
	SetAge(age);

	std::cout << "Birthday, format mm.dd.yyyy: ";
	std::cin >> birthday;
	SetBirthday(birthday);

	std::cout << "Hometown: ";
	std::cin >> hometown;
	SetHometown(hometown);
	
	std::cout << "Current city: ";
	std::cin >> current_city;
	SetCurrentCity(current_city);

	std::cout << "Phone number, format +380XXXXXXXXX: ";
	std::cin >> phone_number;
	SetPhoneNumber(phone_number);

	std::cout << "Current balance: ";
	std::cin >> balance;
	SetBalance(balance);

	std::cout << "\nUsername: ";
	std::cin >> usernameAttempt;
	std::cout << "\nPassword: ";
	std::cin >> passwordAttempt;
	if (!setUsername(usernameAttempt) 
		|| !setPassword(passwordAttempt))
		return false;

	#ifdef _DEBUG_
		std::cout << "Processing the new account user is finished successfully.\n";
	#endif // _DEBUG_
	
	return true;
}

bool Account::load()
{
	ifstream is(reserve_file_name_, ios::in | ios::binary);
	return ((is >> *this) ? true : false);
}

int Account::logIn()
{
	bool i = 0;
	while (i == 0)
	{
		system("cls");
		std::cout << header << menu 
			<< "\n\nChoice: ";
		char operation;
		std::cin >> operation;

		switch (toupper(operation))
		{
		case 'C':
			i = createNewAccount();
			return UNREGISTERED;
			break;
		case 'L':
			return REGISTERED;
		case 'E':
			system("cls");
			std::cout << header
				<< "\n\nLogging out from the Bank.";
			system("pause");
			exit(0);
		}
	}
	
	return true;
}

bool Account::makeTransaction(Account& receiver, double amount)
{
	if ((id_ == receiver.id_) || (receiver.id_ == NULL))
	{
		std::cout << "\nError: Incorrect transaction receiver.";
		system("pause");
		return false;
	}

	std::cout << "\nMaking transaction ...";

	// Checking
	if ((amount <= 0) || (balance_ - amount < 0))
	{
		std::cout << "\nFailure: Not enough money."
		<< "\nOperation: transfering " << amount << "$"
		<< "\nBalance: " << balance_;
		return false;
	}

	// Transfering money
	SetBalance(balance_ - amount);
	receiver.balance_ += amount;

	// Transaction history
	std::ostringstream msg;
	msg << "\nOperation: transfering money;\nSender: " << id_
		<< ";\nReceiver: " << receiver.id_ << ";\nAmount: " << amount
		<< ";\nBalance: " << balance_;
	std::cout << msg.str();
	
	return true;
}

void Account::toUp()
{
	// Checking connection 
	std::string source_name = "g6i8f5t10_c3a8r3d9.txt";
	std::ifstream source(source_name);

	if (!source.good())
	{
		std::cerr << "\nError: To upping has been failed.";
		system("pause");
		return;
	}

	// Reading data
	std::string used = "X";
	double amount = 0.0;

	source >> used >> amount;

	if (used == "X")
	{
		std::cerr << "\nError: You haven't such permission.";
		system("pause");
		return;
	}
	else if (used == "O")
	{
		// Checking data
		if (!checkToUpAmount(amount)) 
		{
			system("pause");
			return;
		}

		// Actually to up
		balance_ += amount;
		std::cout << "\nSuccessful operation.";
		system("pause");

		source.close();
		std::ofstream source(source_name, ios::out);
		source.write("X ", sizeof("X "));
		source << amount;
	}
}

bool Account::checkToUpAmount(double& amount)
{
	if (isdigit(amount) && amount && (amount < 10e9))
	{
		std::cerr << "\nError: Incorrect sum.";
		return false;
	}
	return true;
};

std::ostream& operator<<(std::ostream& os, Account& acc)
{
	if (os.fail())
	{
		cerr << "Error: Outputting account data from std::ostream failed.\n";
		return os;
	}

	#ifdef _DEBUG_
		std::cout << "Outputting is running . . .\n";
	#endif // _DEBUG_

	os << "\n\t\t\tAccount data"
		<< "\nId:\t" << acc.GetID()
		<< "\nFirst name:\t" << acc.GetName()
		<< "\nSurname:\t" << acc.GetSurname()
		<< "\nAge:\t" << acc.GetAge()
		<< "\nBirthday:\t" << acc.GetBirthday()
		<< "\nHometown:\t" << acc.GetHometown()
		<< "\nCurrent city:\t" << acc.GetCurrentCity()
		<< "\nPhone number:\t" << acc.GetPhoneNumber()
		<< "\nBalance:\t" << fixed << setprecision(4) << acc.GetBalance()
		<< "\nUsername:\t" << acc.GetUsername()
		<< "\nPassword:\t" << acc.GetPassword()
		<< '\n';

	#ifdef _DEBUG_
		std::cout << "Outputting has been finished successfully.\n";
	#endif // _DEBUG_

	return os;
}

ofstream& operator<<(ofstream& os, Account& acc)
{
	if (!os.good())
	{
		std::cerr << "\nError: Outputting account data from ofstream failed.";
		return os;
	}

	#ifdef _DEBUG_
		std::cout << "\nOutputting is running . . .";
	#endif // _DEBUG_

	os << acc.GetID()
		<< ' ' << acc.GetName()
		<< ' ' << acc.GetSurname()
		<< ' ' << acc.GetAge()
		<< ' ' << acc.GetBirthday()
		<< ' ' << acc.GetHometown()
		<< ' ' << acc.GetCurrentCity()
		<< ' ' << acc.GetPhoneNumber()
		<< ' ' << std::fixed << setprecision(4) << acc.GetBalance()
		<< ' ' << acc.GetUsername()
		<< ' ' << acc.GetPassword() << ' ';

	#ifdef _DEBUG_
			std::cout << "\nOutputting has been finished successfully.";
	#endif // _DEBUG_

	return os;
}

ifstream& operator>>(ifstream& is, Account& acc)
{
	if (!is.good())
	{
		cerr << "\nError: loading with file "
			<< "users.txt" << " has been failed";
		return is;
	}

	#ifdef _DEBUG_
		std::cout << "\nLoading is running . . .";
	#endif // _DEBUG_

	long long int id = 0;
	string name = "";
	string surname = "";
	unsigned short age = 0;
	string birthday = "";
	string hometown = "";
	string current_city = "";
	string phone_number = "";
	long double balance = 0.0;
	string username = "";
	string password = "";

	is >> id >> name
		>> surname >> age >> birthday
		>> hometown >> current_city
		>> phone_number >> balance
		>> username >> password;

	if (id == 0)
	{
		std::cout << "\nError: Empty user";
		return is;
	}

	acc.SetID(id);
	acc.SetName(name);
	acc.SetSurname(surname);
	acc.SetAge(age);
	acc.SetBirthday(birthday);
	acc.SetHometown(hometown);
	acc.SetCurrentCity(current_city);
	acc.SetPhoneNumber(phone_number);
	acc.SetBalance(balance);
	acc.setUsername(username);
	acc.setPassword(password);

	return is;
}

string Account::reserve_file_name_ = "account.txt";