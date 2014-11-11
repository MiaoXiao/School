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
#include <cstdlib>
#include "IntVector.h"

using namespace std;

//CONSTRUCTOR
/*This function should set both the size and capacity of the IntVector 
to 0 and will not allocate any memory to store integers 
(make sure you do not have a dangling (garbage) pointer).*/
IntVector::IntVector()
	:sz(0), cap(0), data(0){}
	
//CONSTRUCTOR
/*Sets both the size and capacity of the IntVector to the value of the 
parameter passed in and dynamically allocates an array of that size as 
well. (Don't forget to initialize all values in your array to 0.)*/
IntVector::IntVector(unsigned size)
	:sz(size), cap(size), data(new int[size])
{
	//init allocated array with zeros
	initArray(0);
}

//CONSTRUCTOR
/*Sets both the size and capacity of the IntVector to the value of the 
parameter passed in and dynamically allocates an array of that size as 
well. This function should initialize all elements of the array to the 
value of the 2nd parameter.*/
IntVector::IntVector(unsigned size, int value)
	:sz(size), cap(size), data(new int[size])
{
	//init array with value
	initArray(value);
}

/*This function returns the current size (not the capacity) of the IntVector 
object, which is the value stored in the sz data field.*/
unsigned IntVector::size() const
{
	return sz;
}

/*This function returns the current capacity (not the size) of the IntVector 
object, which is the value stored in the cap data field.*/
unsigned IntVector::capacity() const
{
	return cap;
}

/*Returns whether the vector is empty (the sz field is 0).*/
bool IntVector::empty() const
{
	if (sz == 0)
	{
		return true;
	}
	return false;
}

/*This function will return the value stored in the element at the passed in 
index position. Your function should cause the program to exit if an index 
greater than or equal to the size is passed in. Because the index is an 
unsigned int (rather than just int) the compiler will not allow for a negative 
value to be passed in.*/
const int& IntVector::at(unsigned index) const
{
	if (index < sz)
	{
		return data[index];
	}
	exit(1);
}

//PRIVATE//

//initalize entire array with value
void IntVector::initArray(int value) const
{
	for (int i = 0; i < sz; i++)
	{
		*(data + i) = value;
	}
}