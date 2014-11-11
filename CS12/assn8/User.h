//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/User.h
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
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
	private:
		string username;
		string password;
	public:
		//creates a user with empty name and password.
		User()
			:username(""), password(""){}
		// creates a user with given username and password.
		User(const string& uname, const string& pass)
			:username(uname), password(pass){}
		string get_username() const;
		bool check(const string &uname, const string &pass) const;
		void set_password(const string &newpass);
};

#endif