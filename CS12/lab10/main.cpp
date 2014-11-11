//  =============== BEGIN ASSESSMENT HEADER ================
/// @file lab10/main.cpp
/// @brief lab10 for CS 12v Winter 2014
///
/// @author Rica Feng [rfeng001@ucr.edu]
/// @date March 11, 2014
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
#include "Music_collection.h"

using namespace std;

/*
create a few Tune objects to use later on;
Music_collection A;
add a few tunes to A;
Music_collection B(A); 
change a Tune in B using set_tune function;
Music_collection C;
C = B; 
add a Tune to B; 
change a Tune in C using set_tune function;
print A,B,C;
*/

int main()
{
	//create a few Tune objects to use later on;
	Tune tuneA("Clocks");
	Tune tuneB("Australia");
	Tune tuneC("Lazuli");
	Tune tuneD("Feel");
	Tune tuneE("Penny");
	Tune tuneF("Up!");
	Tune tuneG("Touched");
	Tune tuneH("Pangea");
	
	//Music_collection A;
	Music_collection A;
	
	//add a few tunes to A
	if (A.add_tune(tuneA)) { }
	if (A.add_tune(tuneB)) { }
	if (A.add_tune(tuneC)) { }
	if (A.add_tune(tuneD)) { }
	
	Music_collection B(A);
	
	Music_collection C;
	C = B;
	B = B;
	
	return 0;
}