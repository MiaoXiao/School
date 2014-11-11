//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/Reply.h
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
#ifndef REPLY_H
#define REPLY_H

#include <string>
#include <vector>

#include "Message.h"

using namespace std;

class Reply : public Message
{
	// no new member variables
	public:
		//default constructor
		Reply()
			:Message(){}
		/* Parameterized constructor - similar to Message's constructor except:
		* The subject should be initialized to "Re: <sbjct>" not <sbjct>.
		*/
		Reply(const string &athr, const string &sbjct, const string &body, unsigned id)
			:Message(athr, "Re: " + sbjct, body, id){child_list.clear();}
		virtual bool is_reply() const;
		virtual string to_formatted_string() const; // New !!
};

#endif