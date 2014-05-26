#ifndef ITEM_H_
#define ITEM_H_
#include <vector>
#include <fstream>
using namespace std;
class Item
{
public:
	static int Count;
	int min;
	int max;
public:
	int support;
	vector<unsigned int> items;
public:
	Item()
	{
		min = INT_MAX;
		max = -1;
		items.resize(Item::Count, 0);
	}
	Item(int i)
	{
		min = max = i;
		items.resize(Item::Count, 0);
		
		this->setItem(i);
	}
	bool contains(Item *item)
	{
		for (int i = 0; i < Count; i++)
		{
			if ((items[i] & item->items[i]) != item->items[i])
			{
				return false;
			}
		}
		return true;
	}
	int getMaxVal()
	{
		for (int i = Count - 1; i >= 0; i--)
		{
			if (items[i] != 0)
			{
				for (int j = 31; j >= 0; j--)
				{
					if ((items[i] & (1 << j)))
					{
						return i * 32 + j;
					}
				}
			}
		}
	
	}
	int getMinVal()
	{
		for (int i = 0; i < Count; i++)
		{
			if (items[i] != 0)
			{
				for (int j = 0; j < 32; j++)
				{
					if ((items[i] & (1 << j)))
					{
						return i * 32 + j;
					}
				}
			}
		}

	}
	bool join(Item& item, Item& r)
	{
		int K = item.size();
		for (int i = 0; i < Count; i++)
		{
			r.items[i] = (this->items[i] | item.items[i]);
		}
		if (r.size() == K + 1)
		{
			if (max < item.max && min < item.min)
			{
				r.max = item.max;
				r.min = min;
				return true;
			}
		}

		return false;
	}
	void setItem(int c)
	{
		int k = c >> 5;
		int v = c & 0x1f;
		items[k] = (items[k] | (1 << v));
	}
	int size()
	{
		int s = 0;
		unsigned int n;
		for (int i = 0; i < Count; i++)
		{
			n = items[i];
			unsigned int tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
			s +=  ((tmp + (tmp >> 3)) & 030707070707) % 63;
		}
		return s;
	}
	void print(fstream& os)
	{
		
		for (int i = 0; i < Count; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if ((items[i] & (1 << j)))
				{
					os << ((i << 5) + j) << " ";
				}
			}
		}
		os << support <<endl;
	}

	
};
#endif