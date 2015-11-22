//author: Steven Wang Date: 20151028

#include "OrderBook.h"

using namespace std;

OrderBook::OrderBook() {
	map<double, queue<Order>> buy;
	map<double, queue<Order>> sell;
	queue <Order> orders;
}

void OrderBook::TakeOrder(string data) {

	ifstream infile;
	infile.open(data);

	if (infile.fail()) {
		cerr << "Error Opening File" << endl;
		exit(1);
	}

	string ticker;
	string side;
	string type;
	int qty;
	double limitPrice;
	string counterparty;

	while (!infile.eof())
	{
		infile >> ticker >> side >> type >> qty >> limitPrice >> counterparty;

		Order tempOrder(ticker, side, type, qty, limitPrice, counterparty);

		orders.push(tempOrder);

		if (type == "limit") {
			cout << orders.back().GetSide() << " limit order from " << orders.back().GetCounterparty() << ": " << orders.back().Getqty() << " of " << orders.back().GetTicker() << " at limit price $" << orders.back().GetLimitPrice() << " has been accepted." << endl;
		}

		if (type == "market") {
			cout << orders.back().GetSide() << " market order from " << orders.back().GetCounterparty() << ": " << orders.back().Getqty() << " of " << orders.back().GetTicker() << " has been accepted." << endl;
		}

	}

	infile.close();

}

void OrderBook::InputOrder() {

	string ticker;
	string side;
	string type;
	int qty;
	double limitPrice;
	string counterparty;

	cout << "Ticker: " << endl;
	cin >> ticker;

	cout << "Side: " << endl;
	cin >> side;

	cout << "Type: " << endl;
	cin >> type;

	cout << "Quantity: " << endl;
	cin >> qty;

	cout << "Limit Price: " << endl;
	cin >> limitPrice;

	cout << "Counterparty: " << endl;
	cin >> counterparty;

	Order tempOrder(ticker, side, type, qty, limitPrice, counterparty);

	orders.push(tempOrder);

	if (type == "limit") {
		cout << orders.back().GetSide() << " limit order from " << orders.back().GetCounterparty() << ": " << orders.back().Getqty() << " of " << orders.back().GetTicker() << " at limit price $" << orders.back().GetLimitPrice() << " has been accepted." << endl;
	}

	if (type == "market") {
		cout << orders.back().GetSide() << " market order from " << orders.back().GetCounterparty() << ": " << orders.back().Getqty() << " of " << orders.back().GetTicker() << " has been accepted." << endl;
	}

}

void OrderBook::Execution() {
	while (1) {


		if (orders.front().GetSide() == "B") {

			if (orders.front().GetType() == "market") {

				if (sell.size() == 0) {
					//Order tempOrder(ticker, side, type, qty, limitPrice, counterparty);
					buy[999999.99].push(orders.front());
					//deal with it
					cout << orders.front().GetType() << " " << orders.front().GetSide() << " order of " << orders.front().GetTicker() << " from " << orders.front().GetCounterparty() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution." << endl;
					orders.front().Setqty(0);
				}

				while (orders.front().Getqty() > 0) {

					Message message(&(orders.front()), &sell);
					message.BuyExecution();

					if (sell.begin()->second.size() == 0) {
						sell.erase(sell.begin()->first);

					}
				}

				//if the sell orderbook is empty, then add the order to buy orderbook
				if (orders.front().Getqty() > 0) {
					//Order tempOrder(ticker, side, type, qty, limitPrice, counterparty);
					buy[9999.99].push(orders.front());
					//deal with it
					cout << orders.front().GetSide() << " order of " << orders.front().GetTicker() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution." << endl;
				}

			}

			if (orders.front().GetType() == "limit") {

				if (sell.size() == 0 || orders.front().GetLimitPrice() < sell.begin()->second.front().GetLimitPrice()) {
					//Order tempOrder(ticker, side, type, qty, limitPrice, counterparty);
					buy[orders.front().GetLimitPrice()].push(orders.front());
					cout << orders.front().GetType() << " " << orders.front().GetSide() << " order of " << orders.front().GetTicker() << " from " << orders.front().GetCounterparty() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution at $" << orders.front().GetLimitPrice() << endl;

				}

				else {

					while (orders.front().GetLimitPrice() >= sell.begin()->second.front().GetLimitPrice() && orders.front().Getqty() > 0) {

						while (sell.begin()->second.size() != 0 && orders.front().Getqty() > 0) {

							Message message(&(orders.front()), &sell);
							message.BuyExecution();

							//orders.front().Setqty(BuyExecution(orders.front().Getqty(), &sell, orders.front().GetSide(), orders.front().GetTicker(), orders.front().GetLimitPrice(), orders.front().GetCounterparty()));
							//qty = BuyExecution(qty, &sell, side, ticker, limitPrice, counterparty);

						}

						//logic
						if (sell.begin()->second.size() == 0) {
							sell.erase(sell.begin()->first);
						}

					}

					if (orders.front().Getqty() > 0) {
						//Order tempOrder(ticker, side, type, qty, limitPrice, counterparty);
						buy[orders.front().GetLimitPrice()].push(orders.front());
						cout << orders.front().GetSide() << " order of " << orders.front().GetTicker() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution at $" << orders.front().GetLimitPrice() << endl;
					}
				}
			}
		}

		if (orders.front().GetSide() == "S") {

			if (orders.front().GetType() == "market") {

				if (buy.size() == 0) {

					sell[0.0].push(orders.front());
					//deal with it
					cout << orders.front().GetType() << " " << orders.front().GetSide() << " order of " << orders.front().GetTicker() << " from " << orders.front().GetCounterparty() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution." << endl;
					orders.front().Setqty(0);
				}

				while (orders.front().Getqty() > 0) {

					Message message(&(orders.front()), &buy);
					message.SellExecution();
										
					if (buy.rbegin()->second.size() == 0) {
						buy.erase(buy.rbegin()->first);
					}
				}

				//if the buy orderbook is empty, then add the order to buy orderbook
				if (orders.front().Getqty() > 0) {

					sell[0.0].push(orders.front());
					cout << orders.front().GetSide() << " order of " << orders.front().GetTicker() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution." << endl;

				}

			}


			if (orders.front().GetType() == "limit") {

				if (buy.size() == 0 || orders.front().GetLimitPrice() > buy.rbegin()->second.front().GetLimitPrice()) {

					sell[orders.front().GetLimitPrice()].push(orders.front());
					cout << orders.front().GetType() << " " << orders.front().GetSide() << " order of " << orders.front().GetTicker() << " from " << orders.front().GetCounterparty() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution at $" << orders.front().GetLimitPrice() << endl;

				}

				else {

					while (orders.front().GetLimitPrice() <= buy.rbegin()->second.front().GetLimitPrice() && orders.front().Getqty() > 0) {

						while (buy.rbegin()->second.size() != 0 && orders.front().Getqty() > 0) {

							Message message(&(orders.front()), &buy);
							message.SellExecution();

						}

						if (buy.rbegin()->second.size() == 0) {
							buy.erase(buy.rbegin()->first);
						}
					}

					if (orders.front().Getqty() > 0) {

						sell[orders.front().GetLimitPrice()].push(orders.front());
						cout << orders.front().GetSide() << " order of " << orders.front().GetTicker() << ": " << orders.front().Getqty() << " shares are in queue, waiting for execution at $" << orders.front().GetLimitPrice() << endl;
					}

				}
			}
		}

		orders.pop();

		if (orders.size() == 0)
			break;
	}

}



