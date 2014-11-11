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

#ifndef INTVECTOR_H
#define INTVECTOR_H

using namespace std;

class IntVector
{
	private:
		unsigned sz;
		unsigned cap;
		int* data;
	public:
		//CONSTRUCTORS
		IntVector();
		IntVector(unsigned size);
		IntVector(unsigned size, int value);
		//MEMBER FUNCTIONS
		unsigned size() const;
		unsigned capacity() const;
		bool empty() const;
		const int& at(unsigned index) const;
	//PRIVATE FUNCTIONS
	private:
		void initArray(int value) const;
};

#endif