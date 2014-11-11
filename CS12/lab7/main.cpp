//  =============== BEGIN ASSESSMENT HEADER ================
/// @file lab7/main.cpp
/// @brief lab7 for CS 12v Winter 2014
///
/// @author Rica Feng [rfeng001@ucr.edu]
/// @date February 19, 2014
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
#include "IntVector.h"

using namespace std;

void testValues(IntVector test)
{
	cout << "Size: " << test.size() << endl;
	cout << "Capacity: " << test.capacity() << endl;
	cout << "Array: " << endl;
	
	//display array if vector is NOT empty
	if (!test.empty())
	{
		for (int i = 0; i < test.size(); i++)
		{
			cout << "#" << i << ": " << test.at(i);
			cout << endl;
		}
	}
	else
	{
		cout << "Vector is empty!" << endl;
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	//test default constructor (everything 0)
	IntVector test;
	testValues(test);
	
	//test 1 param constructor (size)
	IntVector test2(13);
	testValues(test2);
	
	//test 2 param constuctor (size, value in array)
	IntVector test3(5, 10);
	testValues(test3);
	
	return 0;
}