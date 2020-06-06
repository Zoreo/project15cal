#ifndef __date__
#define __date__
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Date
{
public:
	int day = 0;
	int month = 0;
	int year = 0;

	bool input()
	{
		char temp;
		cin >> day >> temp >> month >> temp >> year;
		if (!(day >= 0 && day < 32 && month > 0 && month <= 12 && year > 1950 && year < 3000))
			return false;
		return true;
	}
	void output() const
	{
		printf("%02d.%02d.%04d", day, month, year);
	}
	int compare(Date& d2) const
	{
		if (year != d2.year)
			return year - d2.year;
		else if (month != d2.month)
			return month - d2.month;
		else
			return  day - d2.day;
	}
	void read(ifstream& fin)
	{
		fin >> day >> month >> year;
	}
	void write(ofstream& fOut)
	{
		fOut << day << " " << month << " " << year << "\n";
	}
};

#endif