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

#ifndef MUSIC_COLLECTION_H
#define MUSIC_COLLECTION_H

#include <string>

using namespace std;

class Tune
{
	private:
		string title;
	public:
		Tune(): title(""){}
		Tune( const string &n ): title(n){}
		const string& get_title() const {return title;}
};

class Music_collection
{
	private: 
		int number; // the number of tunes actually in the collection 
		int max; // the number of tunes the collection will ever be able to hold 
		Tune *collection; // a dynamic array of Tunes: "Music_collection has-many Tunes"
	public:
		// default value of max is a conservative 100
		Music_collection(); 
		// sets max to n
		Music_collection( int n ); 
		// overloaded copy constructor
		Music_collection( const Music_collection &m);
		// returns true if add was successful, 
		// returns false if not enough room to add
		bool add_tune( const Tune &t );
		// sets the Tune at position index in collection to t, 
		// returns true if index < number 
		bool set_tune( int index, const Tune &t );
		// overloaded assignment operator
		Music_collection & operator=( const Music_collection &m );
		// Destructor
		~Music_collection();
		// overloaded stream insertion operator
		// outputs the title of each Tune in the collection on a separate line
		friend ostream & operator<<( ostream &out, const Music_collection &m ); 
};

#endif