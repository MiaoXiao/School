//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/Reply.cpp
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
#include <string>
#include <sstream>

#include "Reply.h"

using namespace std;

// Returns true
bool Reply::is_reply() const
{
	return true;
}

/* to_formatted_string writes the contents of the Reply to a string in the 
* following format:

<begin_reply>
:id: 4
:subject: single line
:from: author
:children: 5 6 [this line should not be printed if there are no 
children.]
:body: multiple lines
2nd line
<end>

* the line starting with :children: has the list of id's of all children 
* (See file specs. for details)
*/
string Reply::to_formatted_string() const  // New !!
{
	//final complete string
	string finalString = "<begin_reply>";
	//buffer to turn int to string
	ostringstream intString;
	
	//convert int id to string
	intString << id;
	
	finalString += "\n:id: " + intString.str();
	finalString += "\n:subject: " + get_subject();
	finalString += "\n:from: " + author;
	
	//check if children exist and append if so
	if (child_list.size() != 0)
	{
		finalString += "\n:children: ";
		for (int i = 0; i < child_list.size(); i++)
		{
			//convert child id to string
			intString << child_list[i]->get_id();
			finalString += intString.str() + " ";
		}
	}
	
	finalString += "\n:body: " + body + "\n<end>";
	
	return finalString;
}