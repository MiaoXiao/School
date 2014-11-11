//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/Message.cpp
/// @brief assn8 for CS 12v Winter 2014
///
/// @author Rica Feng [rfeng001@ucr.edu]
/// @date March 12, 2014
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
#include <string>

#include "Topic.h"
#include "Message.h"

/*
Be very careful here: some Messages will have two pointers to 
them, stored in very different places!
Where are they, and who should be responsible for deleting 
them?
*/
Message::~Message()
{
	for (int i = 0; i < child_list.size(); i++)
	{
		delete child_list[i];
	}
}

//FIX ME
/* This function is responsible for printing the Message 
* (whether Topic or Reply), and and all of the Message's 
* "subtree" recursively:
* After printing the Message with indentation n and appropriate 
* format (see output details), it will invoke itself 
* recursively on all of the Replies in its child_list,
* incrementing the indentation value at each new level.
*
* Note: Each indentation increment represents 2 spaces. e.g. if 
* indentation == 1, the reply should be indented 2 spaces, if 
* it's 2, indent by 4 spaces, etc.
*/ 
void Message::print(unsigned indentation) const
{	
	//copy of indent
	// int count = indentation; 
	
    // for (int i = 0; i < indentation; i++) 
    // { 
        // cout << "  "; 
    // } 
	
    // cout << "Message #" << id << ": " << subject << endl; 
	
    // for (int i = 0; i < indentation; i++) 
    // { 
        // cout << "  "; 
    // } 
	
	//checks child list for more prints
    // cout << "from " << author << ": " << body << endl << endl; 
	
    // for (int i = 0; i < child_list.size(); i++) 
    // { 
        // child_list.at(i)->print(count + 1); 
    // } 
}

//returns the subject string.
const string& Message::get_subject() const
{
	return subject;
}

// returns the id.
unsigned Message::get_id() const
{
	return id;
}

// Adds a pointer to the child to the parent's child_list. 
void Message::add_child(Message *child)
{
	child_list.push_back(child);
}

//displays the message in the given format. See output specs.
/*
void Message::display() const
{
	cout << subject << endl;
	cout << "from " << author << ": " << body << endl;
}
*/
