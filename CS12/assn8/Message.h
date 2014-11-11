//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/Message.h
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
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

using namespace std;

class Message // abstract base class

{
	// allow access to these members by objects of derived classes
	protected:
		string author;
		string subject;
		string body;
		unsigned id; // New !!
		// This will be the size of the message_list vector to which the
		// newly constructed Message * is being pushed_back
		vector<Message*> child_list; // New !!
		// This is how a Message is able to keep track of its Replies
	public:
		// default constructor
		Message()
			:author(""), subject(""), body(""), id(0){child_list.clear();}
		// Parameterized constructor; 
		// id will be the size of current Bboard message_list
		Message(const string &athr, const string &sbjct, const string &body, unsigned id)
			:author(athr), subject(sbjct), body(body), id(id){child_list.clear();}
		virtual ~Message();
		virtual bool is_reply() const = 0; 
		virtual string to_formatted_string() const = 0; // New!!
		void print(unsigned indentation) const; // New !!
		const string & get_subject() const;
		unsigned get_id() const; // New !! 
		void add_child(Message *child); // New !!
		//void display() const;
};

#endif