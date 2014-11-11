//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/main.cpp
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
#include <cstring>
#include "BBoard.h"

using namespace std;

int main(int argc, char *argv[])
{
	//(strcmp(argv[1],"demo")==0) 
	//if no file name given, exit program
    if (strcmp(argv[1], "login") == 0)
    {
        cout << "Usage: " << argv[0] << " <Filename>" << endl;
        return 0;
    }
	string login = argv[1];
	if (strcmp(argv[2], "data") == 0)
    {
        cout << "Usage: " << argv[0] << " <Filename>" << endl;
        return 0;
    }
	string data = argv[2];
	
	//create board instance
	BBoard bb("Rica's Board");
	
	//setup the board with login/pass information, login, then run
	bb.load_users(login);
	bb.load_messages(data);
	bb.login();
	bb.run();
	bb.save_messages(data);
	return 0;
}