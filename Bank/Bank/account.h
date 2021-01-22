#pragma once
#include <iostream>
#include <string>
#include <istream>
class account {
	int id;
	double balance;
	std::string currency;
	std::string password;
public:
	account(int id = 0, std::string password="def", double balance = 0, std::string currency = "EUR") : id(id), password(password), balance(balance), currency(currency) {}
	~account() {}
	friend std::istream& operator>> (std::istream& is, account& acc);
	friend std::ostream& operator<< (std::ostream& os, const account& acc);
	void saveAccount(account& acc);
	account account::getAccount();
	void welcomeDisplay() const;
	void printMenu() const;
	void logRegOption();
	void functionOption(account& account);
	void registerAccount();
	void loginAccount();
	void run();
	void pay();
	void deposit();
	void printBalance() const;
	void exit() const;
	bool balanceCheck(double& amount);
	bool idCheck(int& input_id);
	bool passwordCheck(std::string& input_password);
	void changeCurrency();
	void changeEuro(std::string& wanted);
	void changeKuna(std::string& wanted);
	void changeDollar(std::string& wanted);
	void changePound(std::string& wanted);
	void saveBalance();
	double getBalance();
	void saveCurrency();
	std::string getCurrency();
};
