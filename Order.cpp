//author: Steven Wang Date: 20151028

#include <iostream>

#include <queue>

#include "Order.h"

using namespace std;

Order::Order(string ticker, string side, string type, int qty, double limitPrice, string counterparty) {
	this->ticker = ticker;
	this->side = side;
	this->type = type;
	this->qty = qty;
	this->limitPrice = limitPrice;
	this->counterparty = counterparty;

}

double Order::GetLimitPrice()
{
	return this->limitPrice;
}

string Order::GetTicker() {
	return this->ticker;
}

string Order::GetSide() {
	return this->side;
}

string Order::GetType() {
	return this->type;
}

int Order::Getqty()
{
	return this->qty;
}

void Order::Setqty(int qty) {
	this->qty = qty;
}

string Order::GetCounterparty() {
	return this->counterparty;
}

void Order::SetCounterParty(int counterparty) {
	this->counterparty = counterparty;
}


