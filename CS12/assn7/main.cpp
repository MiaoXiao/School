//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn7/main.cpp
/// @brief assn9 for CS 12v Winter 2014
///
/// @author Rica Feng [rfeng001@ucr.edu]
/// @date March 5, 2014
///
/// @par Enrollment Notes 
///     Lecture Section: NA
/// @par
///     Lab Section: NA
/// @par
///     TA: Juan
///
/// @par Plagiarism Section
/// I hereby certify that the code in this file
/// is ENTIRELY my own original work.
//  =============== END ASSESSMENT HEADER ==================

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

//obtain greatest common denominator
int gcd(int x, int y)
{
    if(y == 0)
	{
		return abs(x);
	}
    else
	{
		return abs(gcd(y, x % y));
	}   
 }
 
bool diophantine(int a, int b, int c, int &x, int &y)
{
	if (c % gcd(a, b) != 0)
	{
		return false;
	}
	if(a % b == 0)
	{
		x = 0;
		y = c / b;
		return true;
	}
	else
	{
		int q = a / b;
		int r = a % b;
		int u = q * (x + y);
		int v = x;
		
		if(diophantine(b, r, c, u, v))
		{
			x = v;
			y = u - q * x;
			return true;
		}
		return false;
	}
}

int main()
{
	//coefficients for equations
	int a, b, c;
	//will hold answers fot equations
	int x, y;
	//hold file names
	string fileNameInput, fileNameOutput;
	
	//ask for user input and output file
	cout << "Enter a input file name: ";
	cin >> fileNameInput;
	cout << endl;
	
	cout << "Enter a output file name: ";
	cin >> fileNameOutput;
	cout << endl;
	
	//declare streams and open them
	ifstream input;
	ofstream output;
	input.open(fileNameInput.c_str());
	output.open(fileNameOutput.c_str());
	
	//while not the end of the file
	while (!input.eof())
	{
		input >> a >> b >> c;
		
		//if true, stream x and y into output file
		if(diophantine(a, b, c, x, y))
		{
			output << x << " " << y << endl;
		}
		//or stream no solution
		else
		{
			output << "No solution!" << endl;
		}
	}
	
	input.close();
	output.close();
	
	return 0;
}