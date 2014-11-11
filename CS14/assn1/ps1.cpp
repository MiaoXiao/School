//Name: Rica Feng
//ID: 861061334
//Date: 10/14/14
//Class: CS14
//Assignment: PS1

#include <iostream>
#include <sstream>
#include <cmath>

#include "fmt.h"

using namespace std;

//std::ostream &operator<<(std::ostream &os, const vectr<T, size> &a)

struct romannumeral
{
	int numeral;
	
	friend ostream &operator<<(ostream &os, const romannumeral& x)
	{
		os << x.numeral;
		return os;
	}
};

struct latlong
{
	double x;
	double y;
};

/*I (for 1), V (for 5), X (for 10), L (for 50), C (for 100), D for (500), and M (for 1000). The only “subtractions”
allowed are IV (for 4), IX (for 9), XL (for 40), XC (for 90), CD (for 400), and CM (for 900)*/
//string converttostring<romannumeral>(romannumeral sample);
template<typename T>
std::string converttostring(T value)
{
	string finished;
	while(value.numeral != 0)
	{
		if(value.numeral / 1000 > 0)
		{
			finished += "M"; 
			value.numeral -= 1000;
		}
		else if(value.numeral / 900 > 0)
		{
			finished += "CM";
			value.numeral -= 900;
		}
		else if(value.numeral / 500 > 0)
		{
			finished += "D";
			value.numeral -= 500;
		}
		else if(value.numeral / 400 > 0)
		{
			finished += "CD";
			value.numeral -= 400;
		}
		else if(value.numeral / 100 > 0)
		{
			finished += "C";
			value.numeral -= 100;
		}
		else if(value.numeral / 90 > 0)
		{
			finished += "XC";
			value.numeral -= 90;
		}
		else if(value.numeral / 50 > 0)
		{
			finished += "L";
			value.numeral -= 50;
		}
		else if(value.numeral / 40 > 0)
		{
			finished += "XL";
			value.numeral -= 40;
		}
		else if(value.numeral / 10 > 0)
		{
			finished += "X";
			value.numeral -= 10;
		}
		else if(value.numeral / 9 > 0)
		{
			finished += "IX";
			value.numeral -= 9;
		}
		else if(value.numeral / 5 > 0)
		{
			finished += "V";
			value.numeral -= 5;
		}
		else if(value.numeral / 4 > 0)
		{
			finished += "IV";
			value.numeral -= 4;
		}
		else
		{
			finished += "I";
			value.numeral -= 1;
		}
	}
	return finished;
}

//Used in converttostring for latlong
//convers double to string
string coordHelper(double value)
{
	//cout << "hello" << endl;
	std::stringstream stream;
	std::string output;
	
	stream << value;
	getline(stream, output);
	return output;
}

string converttostring(latlong sample)
{
	string finished;
	//NORTH OR SOUTH
	if(sample.x >= 0)
	{
		finished += "N" + coordHelper(sample.x);
	}
	else
	{
		finished += "S" + coordHelper(abs(sample.x));
	}
	
	finished += " and ";
	
	//EAST AND WEST
	if(sample.y >= 0)
	{
		finished += "E" + coordHelper(sample.y);
	}
	else
	{
		finished += "W" + coordHelper(abs(sample.y));
	}
	return finished;
}


int main(int argc, char* argv[])
{
	//cout << latlongCoord(latlong().x, latlong().y);
	//cout << romanNumerals(romannumeral().numeral) << endl;
	vector<romannumeral> numerals;
	vector<latlong> coords;	
	
	romannumeral test2;
	
	//init roman numerals vector
	for(int i = 0; i < 13; i++)
	{
		test2.numeral = pow(2,i);
		numerals.emplace_back(test2);
	}
	formatparagraph(cout, numerals, atoi(argv[1]));
	
	latlong test;
	test.x = 33.9756;
	test.y = -117.331;
	
	coords.emplace_back(test);
	
	test.x = 48.8567;
	test.y = 2.3508;
	
	coords.emplace_back(test);
	
	test.x = -16.5;
	test.y = 68.15;
	
	coords.emplace_back(test);
	
	formatparagraph(cout, coords, atoi(argv[1]));
	
	return 0;
}