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

//MUSIC_COLLECTION

// default value of max is a conservative 100
Music_collection::Music_collection()
	: number(0), max(100), collection(new Tune[100]){}

// sets max to n
Music_collection::Music_collection (int n)
	: number(0), max(n), collection(new Tune[n]){}

// overloaded copy constructor
Music_collection::Music_collection (const Music_collection &m)
	:number(m.number), max(m.max), collection(new Tune[m.max])
{
	for (int i = 0; i < m.max; i++)
	{
		collection[i] = m.collection[i];
	}
}

// returns true if add was successful, 
// returns false if not enough room to add
bool Music_collection::add_tune (const Tune &t)
{
	//if at capacity or over, return false
	if (number >= max) return false;
	
	collection[number] = t;
	number++;
	return true;
}

// sets the Tune at position index in collection to t, 
// returns true if index < number 
bool Music_collection::set_tune (int index, const Tune &t)
{
	//return false if index is invalid
	if (index > number) return false;
	
	//allocate new tune	
	collection[index] = t;
	return true;
}

// overloaded assignment operator
Music_collection& Music_collection::operator= (const Music_collection &m)
{
	//do nothing if self assignment
	if (this != &m)
	{
		//deallocate old tunes and allocate empty tunes
		delete []collection;
		collection = new Tune[m.max];
		
		//copy in tunes
		for (int i = 0; i < m.number; i++)
		{
			collection[i] = m.collection[i];
		}
		
		//reassign member variables
		max = m.max;
		number = m.number;
	}
	return *this;
}

// Destructor
Music_collection::~Music_collection()
{
	delete []collection;
}

// overloaded stream insertion operator
// outputs the title of each Tune in the collection on a separate line
ostream & operator<< (ostream &out, const Music_collection &m)
{
	//loop and get titles
	for(int i = 0; i < m.number; i++)
	{
		out << m.collection[i].get_title() << endl;
	}
	return out;
}