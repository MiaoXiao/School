//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/Topic.h
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
#ifndef TOPIC_H
#define TOPIC_H

#include <string>
#include <vector>

#include "Message.h"

using namespace std;

class Topic : public Message
{
	// no new member variables
	public:
		//default constructor
		Topic()
			:Message(){}
		//Parameterized constructor
		Topic(const string &athr, const string &sbjct, const string &body, unsigned id)
			:Message(athr, sbjct, body, id){}
		virtual bool is_reply() const;
		virtual string to_formatted_string() const; // New !!
};

#endif