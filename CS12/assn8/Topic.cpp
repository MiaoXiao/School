//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/Topic.cpp
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

#include "Topic.h"

using namespace std;

// Returns false
bool Topic::is_reply() const
{
	return false;
}

/* writes the contents of the Topic to a 
* string in the following format:

<begin_topic>
:id: 4
:subject: single line
:from: author
:children: 5 6 [this line should not be printed if there are no children.]
:body: multiple lines - line 1
line 2
line 3
<end>

* line starting with :children: has the id's of all children (See file 
specs. 
* for details)
*/

string Topic::to_formatted_string() const // New !!
{
	//final complete string
	string finalString = "<begin_topic>";
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