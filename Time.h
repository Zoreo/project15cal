#ifndef __time__
#define __time__
#include <iostream>
#include <fstream>
#include <cmath>
#include "Date.h"
using namespace std;

class Time
{
public:
	int min = 0;
	int hours = 0;

	bool input()
	{
		char temp;
		cin >> hours >> temp >> min;
		if (!(hours >= 0 && hours < 24 && min >= 0 && min < 60))
			return false;
		return true;
	}
	void output() const
	{
		printf("%02d:%02d", hours, min);
	}
	int compare(Time &t2) const
	{
		if (hours != t2.hours)
			return hours - t2.hours;
		else
			return min - t2.min;
	}
	void read(ifstream& fin)
	{
		fin >> hours >> min;
	}
	void write(ofstream& fOut)
	{
		fOut << hours << " " << min << "\n";
	}
};

#endif