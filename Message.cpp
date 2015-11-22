//author: Steven Wang Date: 20151028

#include "Message.h"

using namespace std;

Message::Message(Order * order, map<double, queue<Order>>* book)
{
	this->order = order;
	this->book = book;
}

int Message::BuyExecution() {

	if ((*order).Getqty() >= (*book).begin()->second.front().Getqty()) {

		cout << (*order).GetSide() << " order of " << (*order).GetTicker() << ": " << (*book).begin()->second.front().Getqty() << " shares have been executed at $" << (*book).begin()->second.front().GetLimitPrice() << ".   Buyer: " << (*order).GetCounterparty() << "    Seller: " << (*book).begin()->second.front().GetCounterparty() << endl;

		(*order).Setqty((*order).Getqty() - (*book).begin()->second.front().Getqty());
		(*book).begin()->second.pop();
	}

	else {
		cout << (*order).GetSide() << " order of " << (*order).GetTicker() << ": " << (*order).Getqty() << " shares have been executed at $" << (*book).begin()->second.front().GetLimitPrice() << ".   Buyer: " << (*order).GetCounterparty() << "    Seller: " << (*book).begin()->second.front().GetCounterparty() << endl;

		(*book).begin()->second.front().Setqty((*book).begin()->second.front().Getqty() - (*order).Getqty());
		(*order).Setqty(0);

	}

	return 0;
}

int Message::SellExecution() {

	if ((*order).Getqty() >= (*book).rbegin()->second.front().Getqty()) {

		cout << (*order).GetSide() << " order of " << (*order).GetTicker() << ": " << (*book).rbegin()->second.front().Getqty() << " shares have been executed at $" << (*book).rbegin()->second.front().GetLimitPrice() << ".   Seller: " << (*order).GetCounterparty() << "    Buyer: " << (*book).rbegin()->second.front().GetCounterparty() << endl;

		(*order).Setqty((*order).Getqty() - (*book).rbegin()->second.front().Getqty());
		(*book).rbegin()->second.pop();
	}
	else {

		cout << (*order).GetSide() << " order of " << (*order).GetTicker() << ": " << (*order).Getqty() << " shares have been executed at $" << (*book).rbegin()->second.front().GetLimitPrice() << ".   Seller: " << (*order).GetCounterparty() << "    Buyer: " << (*book).rbegin()->second.front().GetCounterparty() << endl;

		(*book).rbegin()->second.front().Setqty((*book).rbegin()->second.front().Getqty() - (*order).Getqty());
		(*order).Setqty(0);
	}

	return 0;

}