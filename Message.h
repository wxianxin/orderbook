//author: Steven Wang Date: 20151028

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>

#include <string>

#include <queue>

#include <map>

#include "Order.h"

using namespace std;

class Message {

private:
	Order* order;
	map<double, queue<Order>>* book;
	
public:
	Message(Order* order, map<double, queue<Order>>* book);
	int BuyExecution();
	int SellExecution();
};





#endif