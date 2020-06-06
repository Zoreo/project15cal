#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Calendar.h"
using namespace std;

vector<Event*> events;
vector<Date*> holidays;

string file_name;


void book_event();
void display_all();
void agenda();
void sort_by_start_time();
void sort_by_date();
void un_book();
void open();
void close();
void write();
void save();
void save_as();
bool is_holiday(Date& date);
void find();
void busy_days();
void change();
void find_slot();
void find_slots_with();
void merge();
void help();
int main()
{
	file_name.assign("");
	string option;
	while (option != "exit")
	{
		cin >> option;
		if (option == "book")
		{
			string arg1;
			cin >> arg1;
			if (arg1 == "event")
			{
				book_event();
			}
		}
		else if (option == "agenda")
		{
			agenda();
		}
		else if (option == "unbook")
		{
			un_book();
		}
		else if (option == "open")
		{
			open();
		}
		else if (option == "close")
		{
			close();
		}
		else if (option == "save")
		{
			save();
		}
		else if (option == "saveas")
		{
			save_as();
		}
		else if (option == "all")
		{
			display_all();
		}
		else if (option == "find")
		{
			find();
		}
		else if (option == "busydays")
		{
			busy_days();
		}
		else if (option == "change")
		{
			change();
		}
		else if (option == "findslot")
		{
			find_slot();
		}
		else if (option == "findslotwith")
		{
			find_slots_with();
		}
		else if (option == "merge")
		{
			merge();
		}
		else if (option == "help")
		{
			help();
		}
	}
	return 0;
}


void book_event()
{
	Event* event = new Event();
	if (event->input())
	{
		if (!is_holiday(event->date))
		{
			events.push_back(event);
			cout << "EVENT BOOKED" << endl;
		}
		else {
			cout << "THIS DATE IS HOLIDAY" << endl;
		}
	}
	else
		cout << "Invalid Input" << endl;
}


void display_all()
{
	cout << endl;
	for (int i = 0; i < events.size(); ++i)
	{
		events[i]->output();
		cout << endl;
	}
	cout << endl;
}

void agenda()
{
	Date date;
	if (date.input())
	{
		sort_by_start_time();
		for (int i = 0; i < events.size(); ++i)
		{
			if (events[i]->date.compare(date) == 0)
			{
				events[i]->output();
				cout << endl;
			}
		}
	}
	else
	{
		cout << "INVALID INPUT" << endl;
	}
}

void sort_by_start_time()
{
	const int n = events.size();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (events[j]->startTime.compare(events[j + 1]->startTime) > 0)
			{
				Event* temp = events[j];
				events[j] = events[j + 1];
				events[j + 1] = temp;
			}
}

void sort_by_date()
{
	const int n = events.size();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (events[j]->date.compare(events[j + 1]->date) > 0)
			{
				Event* temp = events[j];
				events[j] = events[j + 1];
				events[j + 1] = temp;
			}
}

void un_book()
{
	Date date;
	Time start_time;
	Time end_time;
	bool validInput = true;
	if (!date.input())
		validInput = false;
	if (!start_time.input())
		validInput = false;
	if (!end_time.input())
		validInput = false;
	if (validInput)
	{
		bool removed = false;
		for (int i = 0; i < events.size(); ++i)
		{
			if (events[i]->date.compare(date) == 0 && events[i]->endTime.compare(end_time) == 0 && events[i]->startTime.compare(start_time) == 0)
			{
				events.erase(events.begin() + i);
				removed = true;
			}
		}
		if (removed)
		{
			cout << "Event canceled" << endl;
		}
		else
		{
			cout << "Event Not Found" << endl;
		}
	}
	else
	{
		cout << "INVALID INPUT" << endl;
	}
}



void open()
{
	cin >> file_name;
	ifstream fin(file_name);
	int size;
	if (fin.is_open())
	{
		fin >> size;
		for (int i = 0; i < size; ++i)
		{
			Event* event = new Event();
			event->read(fin);
			events.push_back(event);
		}
		size = 0;
		fin >> size;
		for (int i = 0; i < size; ++i)
		{
			Date* date = new Date();
			date->read(fin);
			holidays.push_back(date);
		}
		cout << "Successfully opened file " << file_name << endl;
	}
	else
	{
		perror(file_name.c_str());
	}
	fin.close();
}

void write()
{
	ofstream fOut(file_name);
	int size = events.size();
	if (fOut.is_open())
	{
		fOut << size << endl;
		for (int i = 0; i < size; ++i)
		{
			events[i]->write(fOut);
		}
		fOut << holidays.size() << endl;
		for (int i = 0; i < holidays.size(); ++i)
		{
			holidays[i]->write(fOut);
		}
		cout << "Successfully saved file " << file_name << endl;
	}
	else
	{
		perror(file_name.c_str());
	}
	fOut.close();
}

void save()
{
	if (file_name.empty())
	{
		cout << "File Not Opened" << endl;
		return;
	}
	write();
}

void save_as()
{
	string file;
	cin >> file;
	ofstream fOut(file);
	int size = events.size();
	if (fOut.is_open())
	{
		fOut << size << endl;
		for (int i = 0; i < size; ++i)
		{
			events[i]->write(fOut);
		}
		fOut << holidays.size() << endl;
		for (int i = 0; i < holidays.size(); ++i)
		{
			holidays[i]->write(fOut);
		}
		cout << "Successfully saved file " << file << endl;
	}
	else
	{
		perror(file_name.c_str());
	}
	fOut.close();
}

void close()
{
	if (!file_name.empty())
	{
		file_name = "";
		events.clear();
		holidays.clear();
		cout << "Successfully closed file" << file_name << endl;
	}
	else
	{
		cout << "no is not opened" << endl;
	}
}
bool is_holiday(Date& date)
{
	for (int i = 0; i < holidays.size(); ++i)
	{
		if (holidays[i]->compare(date) == 0)
			return true;
	}
	return false;
}

void find()
{
	string to_find;
	cin >> to_find;
	bool found = false;
	for (int i = 0; i < events.size(); ++i)
	{
		if (events[i]->name.find(to_find) != string::npos || events[i]->note.find(to_find) != string::npos)
		{
			cout << endl;
			events[i]->output();
			cout << endl;
			found = true;
		}
	}
	if (!found)
		cout << "No matching event found" << endl;
}

void busy_days()
{
	Date from;
	Date to;
	bool valid_input = true;
	if (!from.input())
		valid_input = false;
	if (!to.input())
		valid_input = false;
	if (valid_input)
	{
		vector<Slots> available_slots;
		vector<Event*> temp;
		for (int i = 0; i < events.size(); ++i)
		{
			if (events[i]->date.compare(from) >= 0 && events[i]->date.compare(to) <= 0)
			{
				temp.push_back(events[i]);
			}
		}

		for (int i = 0; i < temp.size(); ++i)
		{
			bool exist = false;
			for (int j = 0; j < available_slots.size(); ++j)
			{
				if (available_slots[j].date.compare(temp[i]->date) == 0)
				{
					exist = true;
					available_slots[j].add_slot(temp[i]->startTime, temp[i]->endTime);
				}
			}
			if (!exist)
			{
				Slots slot;
				slot.date.year = temp[i]->date.year;
				slot.date.month = temp[i]->date.month;
				slot.date.day = temp[i]->date.day;
				slot.add_slot(temp[i]->startTime, temp[i]->endTime);
				available_slots.push_back(slot);
			}
		}
		const int n = available_slots.size();
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - i - 1; j++)
				if (available_slots[j].hours > available_slots[j + 1].hours)
				{
					Slots temp = available_slots[j];
					available_slots[j] = available_slots[j+1];
					available_slots[j+1] = temp;
				}
		
		for (int i = 0; i < available_slots.size(); ++i)
		{
			available_slots[i].print_busy();
		}
	}
	else
	{
		cout << "Invalid Input" << endl;
	}

}

void change()
{
	Date date;
	Time start_time;
	string option;
	date.input();
	start_time.input();
	Event* event = new Event();
	for (int i = 0; i < events.size(); ++i)
	{
		if (events[i]->date.compare(date) == 0 && events[i]->startTime.compare(start_time) == 0)
		{
			event = events[i];
			break;
		}
	}
	cin >> option;
	if (option == "date")
	{
		event->date.input();
	}
	else if (option == "starttime")
	{
		event->startTime.input();
	}
	else if (option == "endtime")
	{
		event->endTime.input();
	}
	else if (option == "name")
	{
		getline(cin, event->name, '\n');
		if (event->name[0] == ' ')
			event->name = event->name.substr(1);
	}
	else if (option == "note")
	{
		getline(cin, event->note, '\n');
		if (event->note[0] == ' ')
			event->note = event->note.substr(1);
	}
}
void find_slot(vector<Event*>& list, Date& date, int& hours)
{
	vector<Event*> temp;
	vector<Slots> available_slots;
	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i]->date.compare(date) >= 0)
		{
			temp.push_back(list[i]);
		}
	}
	for (int i = 0; i < temp.size(); ++i)
	{
		bool exist = false;
		for (int j = 0; j < available_slots.size(); ++j)
		{
			if (available_slots[j].date.compare(temp[i]->date) == 0)
			{
				exist = true;
				available_slots[j].add_slot(temp[i]->startTime, temp[i]->endTime);
			}
		}
		if (!exist)
		{
			Slots slot;
			slot.date.year = temp[i]->date.year;
			slot.date.month = temp[i]->date.month;
			slot.date.day = temp[i]->date.day;
			slot.add_slot(temp[i]->startTime, temp[i]->endTime);
			available_slots.push_back(slot);
		}
	}
	for (int i = 0; i < available_slots.size(); ++i)
	{
		available_slots[i].print(hours);
	}
}
void find_slot()
{
	Date date;
	int hours;
	int valid = true;
	if (!date.input())
		valid = false;
	cin >> hours;
	if (hours <= 0)
		valid = false;

	sort_by_date();
	find_slot(events, date, hours);
}

void find_slots_with()
{
	Date date;
	int hours;
	int valid = true;
	if (!date.input())
		valid = false;
	cin >> hours;
	if (hours <= 0)
		valid = false;
	vector<string> files_to_read;
	vector<Event*> temp;
	string filenames;
	getline(cin, filenames, '\n');
	stringstream ss(filenames);
	do
	{
		string word;
		ss >> word;
		if (!word.empty())
			files_to_read.push_back(word);
	} while (ss);
	for (int f = 0; f < files_to_read.size(); ++f)
	{
		cout << "Reading \"" << files_to_read[f] << "\"" << endl;

		ifstream fin(files_to_read[f]);
		if (fin.is_open())
		{
			int size;
			fin >> size;
			for (int i = 0; i < size; ++i)
			{
				Event* event = new Event();
				event->read(fin);
				temp.push_back(event);
			}
			cout << "The Available slots of file : " << files_to_read[f] << endl;
			find_slot(temp, date, hours);
		}
		else
		{
			perror(files_to_read[f].c_str());
		}
	}
}

void merge()
{
	vector<string> files_to_read;
	string filenames;
	getline(cin, filenames, '\n');
	stringstream ss(filenames);
	while (ss)
	{
		string word;
		ss >> word;
		if (!word.empty())
			files_to_read.push_back(word);
	}

	vector<Event*> fileEvents;
	vector<Event*> elseEvents;
	vector<Date*> dates;
	ifstream fin(files_to_read[0]);
	if (fin.is_open())
	{
		int size = 0;
		fin >> size;
		for (int i = 0; i < size; ++i)
		{
			Event* e = new Event();
			e->read(fin);
			fileEvents.push_back(e);
		}
		fin >> size;
		for (int i = 0; i < size; ++i)
		{
			Date* date = new Date();
			date->read(fin);
			dates.push_back(date);
		}
		fin.close();
	}
	else
	{
		perror(files_to_read[0].c_str());
		return;
	}
	for (int f = 1; f < files_to_read.size(); ++f)
	{
		ifstream fin(files_to_read[f]);
		if (fin.is_open())
		{
			int size;
			fin >> size;
			for (int i = 0; i < size; ++i)
			{
				Event* e = new Event();
				e->read(fin);
				elseEvents.push_back(e);
			}

			for (int i = 0; i < elseEvents.size(); ++i)
			{
				bool clash = false;
				for (int j = 0; j < fileEvents.size(); ++j)
				{
					if (elseEvents[i]->date.compare(fileEvents[j]->date) == 0)
					{
						if ((elseEvents[i]->startTime.compare(fileEvents[j]->startTime) <= 0
							&& elseEvents[i]->endTime.compare(fileEvents[j]->startTime) >= 0)
							|| (elseEvents[i]->startTime.compare(fileEvents[j]->endTime) <= 0
							&& elseEvents[i]->endTime.compare(fileEvents[j]->endTime) >= 0))
						{
							clash = true;
							cout << "CLASH OCCUR" << endl;
							elseEvents[i]->output();
							cout << "With";
							fileEvents[i]->output();
							cout << "Which one do you want to replace (1/2) : ";
							int op;
							cin >> op;
							if (op == 1)
							{
								fileEvents[j] = elseEvents[i];
							}
						}
					}
				}
				if (!clash)
				{
					fileEvents.push_back(elseEvents[i]);
				}
			}

			fin.close();
		}
		else
		{
			perror(files_to_read[f].c_str());
		}
	}
	ofstream fOut(files_to_read[0]);
	if (fOut.is_open())
	{
		fOut << fileEvents.size() << endl;
		for (int i = 0; i < fileEvents.size(); ++i)
		{
			fileEvents[i]->write(fOut);
		}
		fOut << dates.size()<<endl;
		for (int i = 0; i < dates.size(); ++i)
		{
			dates[i]->write(fOut);
		}
		fOut.close();
	}else
	{
		perror(files_to_read[0].c_str());
	}
	
}

void help()
{
	cout << "The following commands are supported:" << endl;
	cout << "-----------------------------General options----------------------------------------" << endl;
	cout << "	open <file>:       opens <file>" << endl;
	cout << "	close : closes currently opened file" << endl;
	cout << "	save : saves the currently open file" << endl;
	cout << "	saveas <file> : saves the currently open file in <file>" << endl;
	cout << "	help : prints this information" << endl;
	cout << "	exit : exits the program" << endl;
	cout << "-------------------------------Program options--------------------------------------" << endl;
	cout << "	book event <date> <starttime> <endtime> <name> <note> books an event" << endl;
	cout << "	unbook <date> <starttime> <endtime>    unbooks an event" << endl;
	cout << "	agenda <date>       lists all appointments for the date <date>" << endl;
	cout << "	change <date> <starttime> <option> <newvalue>   changes an event" << endl;
	cout << "	find <string>       finds events containing the string<string>" << endl;
	cout << "	holiday <date>      makes the whole date<date> occupied" << endl;
	cout << "	busydays <from> <to>  prints how much work hours you have day by day" << endl;
	cout << "	findslot <fromdate> <hours>  finds free space from a meeting on a date<fromdate>" << endl;
	cout << "	findslotwith <fromdate> <hours> <calendar> finds free space for a meeting on a date<fromdate> synchronized with another calendar(s)" << endl;
	cout << "	merge <calendar>   Transfers all events from other calendar(s) saved in the <calendar> file to the current calendar." << endl;
}

void add_holiday()
{
	Date* date = new Date();
	if (date->input())
	{
		holidays.push_back(date);
		cout << "HOLIDAY ADDED" << endl;
	}
	else
	{
		cout << "Invalid Input" << endl;
	}
}
