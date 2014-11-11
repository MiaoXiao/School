//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/User.cpp
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
#include "User.h"

//returns the username
string User::get_username() const
{
	return username;
}

// returns true if the stored username/password matches with the
// parameters. Otherwise returns false.
// Note that, even though a User with empty name and password is 
// actually a valid User object (it is the default User), this 
// function must still return false if given a empty uname string.
bool User::check(const string &uname, const string &pass) const
{
	if (username == "" || password == "")
	{
		return false;
	}
	else if (username == uname && password == pass)
	{
		return true;
	}
	return false;
}

// sets a new password. This function will not be used in the 
// current assignment.
void User::set_password(const string &newpass)
{
	password = newpass;
}
