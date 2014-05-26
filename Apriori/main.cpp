#include <iostream>
#include"Item.h"
#include "Apriori.h"
#include <time.h>
using namespace std;
//this number is decided by status number...
int Item::Count = 4; //mashroom.data
int main()
{
	Apriori apriori(120);
	apriori.loadDatFile("mushroom.dat");
	apriori.setSupportDegree(0.25);
	clock_t t1, t2;
	t1 = clock();
	apriori.run();
	t2 = clock();
	cout << t2 - t1<<endl;
	fstream os("result.txt", ios::out);
	apriori.print(os);
}