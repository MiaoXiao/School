#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date
{
	private:
		unsigned day;
		unsigned month;
		string monthName;
		unsigned year;
	public:
		Date ();
		Date (unsigned, unsigned, unsigned);
		Date (const string &, unsigned, unsigned);
		Date addDays(int) const;
		void printNumeric () const;
		void printAlpha () const;
	private:
		bool isLeap (unsigned) const;
		unsigned daysPerMonth (unsigned, unsigned) const;
		string name (unsigned) const;
		unsigned number (const string &) const;
};
#endif