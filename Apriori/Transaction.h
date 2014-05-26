#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <vector>
#include "Item.h"
using namespace std;

class Transaction
{
private:
	Item items;
public:
	Transaction()
	{

	}
	void push(int val)
	{
		items.setItem(val);
	}
	bool contains(Item* item)
	{
		return items.contains(item);
	}
};
#endif