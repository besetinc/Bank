#pragma once
#include <string>
#include "account.h"
class bill : public account {
	std::string name, currency;
	int id, amount;
public:
	bill(std::string name="def", int id=0, int amount=0, std::string currency="def") : name(name), id(id), amount(amount), currency(currency) {}
	~bill(){}
	bill createBills(account& a);
	void printBills(bill b[4]);
	void billOption(bill b[4],account& a);
};
