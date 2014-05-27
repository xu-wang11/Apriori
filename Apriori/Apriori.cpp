#include "Apriori.h"
#include <fstream>
#include <string>
#include <list>
#include<iostream>
using namespace std;


void Apriori::loadDatFile(char* path)
{
	fstream os(path, ios::in);
	char buffer[4096];
	while (!os.eof())
	{
		memset(buffer, 0, sizeof(char)* 4096);
		os.getline(buffer, 4096);
		if (strlen(buffer) <= 0)
			continue;
		string str(buffer);
		Transaction t;
		while (str.length() != 0)
		{
			int loc = str.find_first_of(' ');
			if (loc > 0)
			{
				int val = atoi(str.substr(0, loc).data());
				t.push(val);
			}
			else
			{
				int val = atoi(str.data());
				t.push(val);
			}
			str = str.substr(loc + 1);
		}
		transactions.push_back(t);
	}
	
}
void Apriori::run()
{

	//calculate support according to support degree
	this->support = this->supportDegree * this->transactions.size();
	list<Item> K;
	list<Item> KPlus;
	//generate the first generator
	//K.resize(ItemCount);
	for (int i = 0; i < ItemCount; i++)
	{
		K.push_back(Item(i));
	}
	list<Item>::iterator it;
	for (it = K.begin(); it != K.end(); it++)
	{
		it->support = this->calculateSupport(&(*it));
	}
	filter(K);
	addToResult(K);
	while (K.size() > 1)
	{
		cout << K.size() << " " << K.begin()->size()<<endl;
		generateNext(K, KPlus);
		addToResult(KPlus);
		
		K.clear();
		
		K.insert(K.begin(), KPlus.begin(), KPlus.end());
		KPlus.clear();
	}
	
}

//generate k+1 gap for item collection K
void Apriori::generateNext(list<Item>&items1, list<Item>&items2)
{
	list<Item>::iterator it;
	list<Item>::iterator it2;
	list<Item>::iterator it3;
	bool isJoin;
	
	int n = items1.size();
	if (n < 2)
	{
		items2.clear();
		return;
	}
	int K = items1.begin()->size();
	for (it = items1.begin(); it != items1.end(); it++)
	{
		for (it2 = it, it2++; it2 != items1.end(); it2++)
		{
			Item item;
			isJoin = (*it).join(*it2, item);
			if (isJoin)
			{
				int contain = 0;
				for (it3 = items1.begin(); it3 != items1.end(); it3++)
				{
					if (item.contains(&(*it3)))
					{
						contain++;
						if (contain == K + 1)
							break;
					}
				}
				if (contain == K + 1)
				{
					item.support = this->calculateSupport(&item);
					if (item.support >= this->support)
					{
						items2.push_back(item);
					}
				}
				
				
				
			}
		}
	}
}

//filter the one whose support < threshold
void Apriori::filter(list<Item>& items)
{
	list<Item>::iterator it;
	for (it = items.begin(); it != items.end(); )
	{
		if (it->support < this->support)
		{
			it = items.erase(it);
		}
		else
			it++;
	}
}

//add result 
void Apriori::addToResult(list<Item>& items)
{
	list<Item>::iterator it;
	for (it = items.begin(); it != items.end(); it++)
		this->ResultArray.push_back(*it);
}

//caluclate the support of item
int Apriori::calculateSupport(Item* item)
{
	int size = transactions.size();
	int support = 0;
	for (int i = 0; i < size; i++)
	{
		support += transactions[i].contains(item);
	}
	return support;
}

//print the result
void Apriori::print(fstream& os)
{
	list<Item>::iterator it;
	for (it = this->ResultArray.begin(); it != this->ResultArray.end(); it++)
	{
		it->print(os);
	}
}
