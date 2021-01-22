#include "account.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>
void account::welcomeDisplay() const {
	std::cout << "Welcome to the ATM, please select one of the following options." << std::endl;
	std::cout << "Option 1 - Login" << std::endl;
	std::cout << "Option 2 - Register" << std::endl;
}
void account::run() {
	welcomeDisplay();
	logRegOption();
}
void account::saveBalance() {
	using namespace std;
	vector <double>a;
	a.push_back(balance);
	ofstream f("b_log.txt");
	copy(a.begin(), a.end(), ostream_iterator<double>(f, "\n"));
}
std::istream& operator >> (std::istream& is, account& acc) {
	is >> acc.id >> acc.password;// >> acc.balance >> acc.currency;
	return is;
}
std::ostream& operator<< (std::ostream& os, const account& acc) {
	os << acc.id << " " << acc.password;// << " " << acc.balance << " " << acc.currency;
	return os;
}
void account::saveAccount(account& acc) {
	using namespace std;
	ofstream f("users.txt");
	vector<account> v;
	v.push_back(acc);
	copy(v.begin(), v.end(), ostream_iterator<account>(f, " "));
}
double account::getBalance() {
	using namespace std;
	ifstream f("b_log.txt");
	vector<double> b;
	istream_iterator<double> is(f), eof;
	copy(is, eof, back_inserter(b));
	return b.at(0);
}
void account::saveCurrency() {
	using namespace std;
	vector <string>a;
	a.push_back(currency);
	ofstream f("c_log.txt");
	copy(a.begin(), a.end(), ostream_iterator<string>(f, "\n"));
}
std::string account::getCurrency() {
	using namespace std;
	ifstream f("c_log.txt");
	vector<string> b;
	istream_iterator<string> is(f), eof;
	copy(is, eof, back_inserter(b));
	return b.at(0);
}
account account::getAccount() {
	using namespace std;
	ifstream f("users.txt");
	vector<account> b;
	istream_iterator<account> is(f), eof;
	copy(is, eof, back_inserter(b));
	return b.at(0);
}
void account::printMenu() const {
	std::cout << "\nSelect one of the following options:" << std::endl;
	std::cout << "Option 1 - Pay" << std::endl;
	std::cout << "Option 2 - Deposit" << std::endl;
	std::cout << "Option 3 - Display balance" << std::endl;
	std::cout << "Option 4 - Currency change" << std::endl;
	std::cout << "Option 5 - Exit" << std::endl;
}
void account::logRegOption() {
	int option=0; std::cin >> option;
	switch (option) {
	case 1: loginAccount(); break;
	case 2: registerAccount(); break;
	}
}

void account::registerAccount() {
	std::cout << "You are about to create your account." << std::endl;
	std::cout << "Enter wanted Id." << std::endl;
	std::cin >> id;
	std::cout << "Enter wanted password." << std::endl;
	std::cin >> password;
	std::cout << "Enter wanted currency." << std::endl;
	std::cin >> currency;
	account r1(id, password, 0, currency);
	std::cout << "You have succesfully created your bank account." << std::endl;
	saveAccount(r1);
	r1.saveCurrency();
	printMenu();
	r1.functionOption(r1);
}
void account::loginAccount() {
	account r1(getAccount());
	r1.balance=getBalance();
	r1.currency=getCurrency();
	int input_id = 0; std::string input_password="";
		std::cout << "Please enter your Id." << std::endl;
		std::cin >> input_id;
		std::cout << "Please enter your password." << std::endl;
		std::cin >> input_password;
		if (!r1.passwordCheck(input_password) || !r1.idCheck(input_id)) {
			std::cout << "Password or id incorrect.";
		}
		else {
			printMenu();
			r1.functionOption(r1);
		}
}
void account::functionOption(account& account) {
	int option = 0;
	while (option != 5) {
		std::cin >> option;
		switch (option) {
		case 1: account.pay(); break;
		case 2: account.deposit(); break;
		case 3: account.printBalance(); break;
		case 4: account.changeCurrency(); break;
		case 5: account.saveBalance(); account.saveCurrency(); exit(); break;
		}
	}
}
void account::pay() {
	std::cout << "Enter the amount to pay." << std::endl;
	double amount=0; std::cin >> amount;
	if (balanceCheck(amount)) {
		balance -= amount;
		std::cout << "You have succesfully paid an amount of : " << amount << " " << currency << std::endl;
	}
	else {
		std::cout << "You don't have enough funds to pay this amount." << std::endl;
	}
	printMenu();
}
void account::deposit() {
	std::cout << "Enter the amount to deposit." << std::endl;
	double amount=0; std::cin >> amount;
	balance += amount;
	std::cout << "You have succesfully deposited an amount of : " << amount << " " << currency << std::endl;
	printMenu();
}
void account::printBalance() const {
	std::cout << "Balance for account number " << id << " is : " << std::fixed << std::setprecision(2) << balance << " " << currency << std::endl;
	printMenu();
}
void account::exit() const {
	std::cout << "Thank you for using our ATM, goodbye!";
}
bool account::balanceCheck(double& amount) {
	return (balance - amount) >= 0;
}
bool account::passwordCheck(std::string& input_password) {
	return input_password == password;
}
bool account::idCheck(int& input_id) {
	return id == input_id;
}
void account::changeCurrency() {
	std::cout << "Please enter wanted currency, we support KN - USD - GBP - EUR, your currency is " << currency << "." << std::endl;
	std::string wanted; std::cin >> wanted;
	if (currency == "EUR" ) changeEuro(wanted);
	else if (currency == "KN") changeKuna(wanted);
	else if (currency == "USD") changeDollar(wanted);
	else if (currency == "GBP") changePound(wanted);
	printBalance();
}
void account::changeEuro(std::string& wanted) {
	if (wanted == "KN") { balance *= 7.581251; currency = "KN"; }
	else if (wanted == "USD") { balance *= 1.083433; currency = "USD"; }
	else if (wanted == "GBP") { balance *= 0.886135; currency = "GBP";
	}
}
void account::changeKuna(std::string& wanted) {
	if (wanted == "EUR") { balance *= 0.13; currency = "EUR"; }
	else if (wanted == "USD") { balance *= 0.14; currency = "USD"; }
	else if (wanted == "GBP") { balance *= 0.12; currency = "GBP"; }
}
void account::changeDollar(std::string& wanted) {
	if (wanted == "EUR") { balance *= 0.92; currency = "EUR"; }
	else if (wanted == "KN") { balance *= 6.993129; currency = "KN"; }
	else if (wanted == "GBP") { balance *= 0.82; currency = "GBP"; }
}
void account::changePound(std::string& wanted) {
	if (wanted == "EUR") { balance *= 1.12850; currency = "EUR"; }
	else if (wanted == "USD") { balance *= 1.22; currency = "USD"; }
	else if (wanted == "KN") { balance *= 8.601374; currency = "KN"; }
}