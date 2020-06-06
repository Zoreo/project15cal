#ifndef __slots__
#define __slots__
#include <iostream>
#include <fstream>
#include <cmath>
#include "Time.h"
using namespace std;

class Slots
{
public:
	Date date;
	bool slots[24];
	int hours = 0;
	int min = 0;
	
	Slots()
	{
		for (int i = 0; i < 24; ++i)
			slots[i] = false;
	}
	void add_slot(Time &start,Time &end)
	{
		hours = hours + (end.hours - start.hours);
		min = end.min - start.min;
		if(min<0)
		{
			hours--;
			min = 60 - min;
		}
		int s = start.hours;
		int e = end.hours;
		if (start.min > 0)
			s++;
		if (end.min > 0)
			e++;
		for (int i = s; i <= e; ++i)
		{
			slots[i] = true;
		}
	}
	void print()
	{
		cout << "AVAILABLE SLOTS FOR DATE ";
		date.output();
		cout << endl;
		for (int i = 0; i < 24; ++i)
		{
			if(slots[i]==false)
			{
				Time time;
				time.min = 0;
				time.hours = i;
				time.output();
				cout << endl;
			}
		}
	}
	void print(int hours)
	{
		cout << "AVAILABLE SLOTS FOR DATE ";
		date.output();
		cout << endl;
		for (int i = 8; i < 18; ++i)
		{
			if(slots[i]==false)
			{
				int f = 0;
				for (int j = i; j < 18; ++j)
				{
					if(slots[j]==true)
						break;
					f++;
				}
				if (f >= hours) {
					Time time;
					time.min = 0;
					time.hours = i;
					time.output();
					cout << endl;
				}
			}
		}
	}
	void print_busy()
	{
		cout << "Date : ";
		date.output();
		printf(" : %0d:%02d", hours, min);
		cout << endl;
	}
};

#endif