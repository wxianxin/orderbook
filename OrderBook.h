//author: Steven Wang Date: 20151028

#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include <iostream>

#include <queue>

#include <map>

#include <fstream>

#include "Order.h"

#include "Message.h"

using namespace std;

class OrderBook {
	
private:
	queue <Order> orders;
	map<double, queue<Order>> buy;
	map<double, queue<Order>> sell;
	ifstream infile;

public:
	OrderBook();
	void TakeOrder(string data);
	void InputOrder();
	void Execution();
};




#endif