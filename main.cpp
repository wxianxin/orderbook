//author: Steven Wang Date: 20151028

#include <iostream>

#include <string>

#include "OrderBook.h"

using namespace std;


int main() {

	OrderBook orderBook;
	
	orderBook.TakeOrder("data.txt");

	orderBook.Execution();

	char yn;

	while (1) {
		cout << "Do you want input a new order?(y/n)" << endl;
		cin >> yn;

		if (yn == 'y') {
			orderBook.InputOrder();
			orderBook.Execution();
		}
		if (yn == 'n') {
			break;
		}
	}

	return 0;
}