#include <iostream>
#include "Date.h"

using namespace std;

////////////////PUBLIC///////////////

//default constructor: creates the date January 1st, 2000.
Date::Date()
{
	day = 1;
	month = 1;
	monthName = "January";
	year = 2000;
}

//para constructor: month number, day, year
	//ex(3, 1, 2010)
Date::Date (unsigned m, unsigned d, unsigned y)
{
	//will change to true if incorrect input
	bool wrong = false;
	
	//if invalid month input, change to closest month
	if (m < 1)
	{
		m = 1;
		wrong = true;
	}
	else if (m > 12)
	{
		m = 12;
		wrong = true;
	}
	
	//if invalid day input, change to closest day
	if (d > daysPerMonth(m, y))
	{
		d = daysPerMonth(m,y);
		wrong = true;
	}
	
	//assign all variables
	day = d;
	month = m;
	monthName = name(m);
	year = y;
	
	//outputs message if input was wrong
	if (wrong)
	{
		cout << "Invalid date values: Date corrected to ";
		cout << month << "/" << day << "/" << year << "." << endl;
	}
}

//para constructor: month name, day, year
	//ex(December, 15, 2012)
Date::Date (const string &mName, unsigned d, unsigned y)
{
	//will change to true if invalid day
	bool wrongDay = false;
	//will change to true if invalid month
	bool wrongMonth = false;
	
	if (mName == "January" || mName == "january")
	{	
		month = number("January");
		monthName = "January";
	}
	else if (mName == "February" || mName == "february")
	{
		month = number("February");
		monthName = "February";
	}
	else if (mName == "March" || mName == "march")
	{
		month = number("March");
		monthName = "March";
	}
	else if (mName == "April" || mName == "april")
	{
		month = number("April");
		monthName = "April";
	}
	else if (mName == "May" || mName == "may")
	{
		month = number("May");
		monthName = "May";
	}
	else if (mName == "June" || mName == "june")
	{
		month = number("June");
		monthName = "June";
	}
	else if (mName == "July" || mName == "july")
	{
		month = number("July");
		monthName = "July";
	}
	else if (mName == "August" || mName == "august")
	{
		month = number("August");
		monthName = "August";
	}
	else if (mName == "September" || mName == "september")
	{
		month = number("September");
		monthName = "September";
	}
	else if (mName == "October" || mName == "october")
	{
		month = number("October");
		monthName = "October";
	}
	else if (mName == "November" || mName == "november")
	{
		month = number("November");
		monthName = "November";
	}
	else if (mName == "December" || mName == "december")
	{
		month = number("December");
		monthName = "December";
	}
	//If invalid month name, change date to 1/1/2000
	else
	{
		day = 1;
		month = number("January");
		monthName = "January";
		year = 2000;
		
		wrongMonth = true;
	}

	//if monthName is correct but day number is invalid, change to closest day
	if ((!wrongMonth) && (d > daysPerMonth(month, y)))
	{
		day = daysPerMonth(month,y);
		wrongDay = true;
	}
	
	//outputs message if input was wrong
	if (wrongDay || wrongMonth)
	{
		cout << "Invalid date values: Date corrected to ";
		if (wrongDay)
		{
			year = y;
		}
		cout << month << "/" << day << "/" << year << "." << endl;
	}
	//all inputs correct, assign remaining variables!
	else
	{
		day = d;
		year = y;
	}
}

// Add a number of days to one date to get another: 
// this number may be positive or negative.
// Obviously, the new date will have to be a valid date, 
// accounting for the correct number of days in each month, 
// and for leap years.
Date Date::addDays(int increment) const
{
	//new instance to hold new date
	Date x(month, day, year);
	
	int value = (static_cast<int>(x.day) + increment);
	//cout << "orig value " << value << endl;
	
	//Move up months
	while (value > daysPerMonth(x.month, x.year) && value > 0)
	{
		//cout << "POS " << endl;
		value -= daysPerMonth(x.month, x.year);
		x.month++;
		if (x.month > 12)
		{
			x.month = 1;
			x.year++;
		}
	}
	
	//move down months
	while (value < 1)
	{
		//cout << "NEG " << endl;
		x.month--;
		if (x.month == 0)
		{
			x.month = 12;
			x.year--;
		}
		value = daysPerMonth(x.month, x.year) + value;
		//cout <<"value " << value << endl;
	}
	x.day = value;
	
	return x;
}

//const accessor function to output a Date exactly in the format "3/1/2012". 
void Date::printNumeric () const
{
	cout << month << "/" << day << "/" << year;
}

//const accessor function to output a Date exactly in the format "March 1, 2012".
	//must be capitalized month
void Date::printAlpha () const
{
	cout << monthName << " " << day << ", " << year;
}

////////////////PRIVATE///////////////

//tests for leap year
bool Date::isLeap(unsigned y) const
{
	//implies leap year 
	if (y % 4 == 0)
	{
		//does not imply leap year
		if (y % 100 == 0)
		{
			//unless its a multiple of 400
			if (y % 400 == 0)
			{
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

//returns number of days allowed in a given month
unsigned Date::daysPerMonth(unsigned m, unsigned y) const
{
	//31 days
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		return 31;
	}
	//30 days
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		return 30;
	}
	//check feb in case of leap year
	else if (isLeap(y))
	{
		return 29;
	}
	//if no other value was returned, it must be feb on a non leap year
	return 28;
}

//returns name of a given month
string Date::name(unsigned m) const
{
	//if invalid month input, change to closest month
	if (m <= 1)
	{
		return "January";
	}
	else if (m >= 12)
	{
		return "December";
	}
	
	//change to month name according to month number
	if (m == 2)
	{
		return "February";
	}
	else if (m == 3)
	{
		return "March";
	}
	else if (m == 4)
	{
		return "April";
	}
	else if (m == 5)
	{
		return "May";
	}
	else if (m == 6)
	{
		return "June";
	}
	else if (m == 7)
	{
		return "July";
	}
	else if (m == 8)
	{
		return "August";
	}
	else if (m == 9)
	{
		return "September";
	}
	else if (m == 10)
	{
		return "October";
	}
	else if (m == 11)
	{
		return "November";
	}
}
		
//returns number of a given named month
unsigned Date::number(const string &mName) const
{
	if (mName == "January")
	{
		return 1;
	}
	else if (mName == "February")
	{
		return 2;
	}
	else if (mName == "March")
	{
		return 3;
	}
	else if (mName == "April")
	{
		return 4;
	}
	else if (mName == "May")
	{
		return 5;
	}
	else if (mName == "June")
	{
		return 6;
	}
	else if (mName == "July")
	{
		return 7;
	}
	else if (mName == "August")
	{
		return 8;
	}
	else if (mName == "September")
	{
		return 9;
	}
	else if (mName == "October")
	{
		return 10;
	}
	else if (mName == "November")
	{
		return 11;
	}
	else if (mName == "December")
	{
		return 12;
	}
}

