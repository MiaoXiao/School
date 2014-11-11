//Name: Rica Feng
//ID: 861061334
//Date: 10/14/14
//Class: CS14
//Assignment: PS1

#ifndef FMT_H
#define FMT_H

#include <iostream>
#include <vector>
#include <sstream>
#include <ostream>

template<typename T>
void formatparagraph(std::ostream &os, const std::vector<T> &v, int width)
{
	std::string currentString;
	int currentWidth = 0;

	for (int i = 0; i < v.size(); i++)
	{
		//convert data type to string
		currentString = converttostring(v.at(i));
		
		//if string cannot fit within width, add newline first and set currentwidth to new string size + 1
		if(currentString.size() + currentWidth > width)
		{
			std::cout << std::endl;
			os << currentString << " " ;
			currentWidth = currentString.size() + 1;
		}
		//else just print string, add space, and add size of string + 1 to currentwidth
		else
		{
			//print string
			os << currentString << " " ;
			currentWidth += currentString.size() + 1;
		}
	}
	//last endline
	std::cout << std::endl;
}

/*
using namespace std;

struct spreadsheetcell 
{
	spreadsheetcell (string c , int r) 
		:col(c) ,row(r) {}
	string col;
	int row;
};
	
string converttostring ( const spreadsheetcell & ssc ) 
{
	return ssc.col + to_string(ssc.row);
}


int main()
{
	vector <spreadsheetcell> v;
	for(int i = 1; i <= 4; i++) 
	{
		v.emplace_back("A", i);
		v.emplace_back("AZ", i);
		v.emplace_back("BBD", i);
		v.emplace_back("Z", i);
	}
	
	formatparagraph (cout, v ,18);
	
	return 0;
	
	//A1 AZ1 BBD1 Z1 A2
	//AZ2 BBD2 Z2 A3 AZ3
	//BBD3 Z3 A4 AZ4
	//BBD4 Z4
}
*/
#endif