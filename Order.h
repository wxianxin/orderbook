//author: Steven Wang Date: 20151028

#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>

using namespace std;

class Order {

private:
	string ticker;
	string side;
	string type;
	int qty;
	double limitPrice;
	string counterparty;


public:
	Order(string ticker, string side, string type, int qty, double limitPrice, string counterParty);	
	double GetLimitPrice();
	string GetTicker();
	string GetSide();
	string GetType();
	int Getqty();
	void Setqty(int qty);
	void SetCounterParty(int counterparty);
	string GetCounterparty();

};

#endif