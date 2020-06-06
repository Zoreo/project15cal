#ifndef __calender__
#define __calender__
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



class Event
{
public:
	Date date;
	Time startTime;
	Time endTime;
	string name;
	string note;

	bool input()
	{
		bool valid = true;
		cout << "Date       : ";
		if (!date.input())
			valid = false;
		cout << "Start Time : ";
		if (!startTime.input())
			valid = false;
		cout << "End Time   : ";
		if (!endTime.input())
			valid = false;
		cout << "Name       : ";
		cin.ignore();
		getline(cin, name, '\n');
		cout << "Note       : ";
		getline(cin, note, '\n');
		return valid;
	}
	void output() const
	{
		cout << endl;
		cout << "Date       : ";
		date.output();
		cout << endl;
		cout << "Start Time : ";
		startTime.output();
		cout << endl;
		cout << "End Time   : ";
		endTime.output();
		cout << endl;
		cout << "Name       : ";
		cout << name;
		cout << endl;
		cout << "Note       : ";
		cout << note;
		cout << endl;
	}
	
	void read(ifstream &fin)
	{
		date.read(fin);
		startTime.read(fin);
		endTime.read(fin);
		fin.ignore();
		getline(fin, name);
		getline(fin, note);
	}

	void write(ofstream &fOut)
	{
		date.write(fOut);
		startTime.write(fOut);
		endTime.write(fOut);
		fOut << name << "\n";
		fOut << note << "\n";
	}
};

int calculate_hours(Time &t1,Time &t2)
{
	return abs(t1.hours - t2.hours);
}

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
