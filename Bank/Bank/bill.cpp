#include "bill.h"
#include "account.h"
#include <iomanip>
bill bill::createBills(account& a) {
	bill b[4] = { {"Electric",1,49,"EUR"},{"Internet", 2, 27, "EUR"},{"Water", 3, 36, "EUR"},{"Gas", 4, 61, "EUR"} };
	return b[4];
}
void bill::printBills(bill b[4]) {
	for (int i = 0; i < 4; ++i) {
		if (b[i].id = 0) {
			continue;
		}
		int len = b[i].name.length();
		std::cout << "Name: " << std::setw(len) << b[i].name << std::setw(10) << "Amount: " << b[i].amount << " " << b[i].currency << std::endl;
	}
}

void bill::billOption(bill b[4],account& a) {
	std::cout << "Select a bill you want to pay." << std::endl;
	int option = 0; std::cin >> option;
	switch (option) {
	case 1:
		b[0].id = 0;
		a.paySpecific(b[0].amount);
		a.printMenu();
		break;
	case 2:
		b[1].id = 0;
		a.paySpecific(b[1].amount);
		a.printMenu();
		break;
	case 3:
		b[2].id = 0;
		a.paySpecific(b[2].amount);
		a.printMenu();
		break;
	case 4:
		b[3].id = 0;
		a.paySpecific(b[3].amount);
		a.printMenu();
		break;
	}
}