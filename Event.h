#ifndef __event__
#define __event__
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Time.h"
using namespace std;

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

#endif
