#ifndef APRIORI_H_
#define APRIORI_H_
#include <list>
#include <fstream>
#include "Transaction.h"
using namespace std;

/*
* implement apriori algorithm.
*/
class Apriori
{
private:
	double supportDegree;
	int support;
	int ItemCount;
	vector<Transaction> transactions;
	list<Item> ResultArray;
	//vector<int>  SupportArray;
public:
	Apriori(int c)
	{
		ItemCount = c;
	}
	//load data from file
	void loadDatFile(char* path);
	//set
	void setSupportDegree(double supportDegree)
	{
		this->supportDegree = supportDegree;
	}
	//generate the next generation itemcollection
	void generateNext(list<Item> &items1, list<Item>&items2);
	//filter useless status
	void filter(list<Item> & items);
	//add result to list
	void addToResult(list<Item>&items);
	//calculate support
	int calculateSupport(Item* item);
	void run();
	void print(fstream& os);
};
#endif