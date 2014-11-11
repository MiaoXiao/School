//  =============== BEGIN ASSESSMENT HEADER ================
/// @file lab9/main.cpp
/// @brief lab9 for CS 12v Winter 2014
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

using namespace std;

void reverse(string &s)
{	
	if (s.size() > 1)
	{
		string temp = s.substr(1, s.size() - 2);
		reverse(temp);
		s = s.substr(s.size() - 1) + temp + s.at(0);
	}
}

int main()
{
	string test = "Tacocat";
	cout << "Original: " << test << endl;
	reverse(test);
	cout << "Final: " << test << endl;
	return 0;
}