#include <iostream>
#include "BBoard.h"

using namespace std;

/*
In the main function, you should create a BBoard object e.g., BBoard bb
( user_bb_title );, giving the 
title any name you want, and then import the list of authorized users with setup
(name of input file). The name 
of the input file you pass into the setup function will be a command line 
argument. This file will be in the same 
directory as the executable.
Next, use the login function to display a welcome message, and then ask the 
user to login (provide username and 
password); the function then sets the current_user (or quits).
Finally you'll just call the run function which includes the main loop.*/

int main(int argc, char *argv[])
{
	//if no file name given, exit program
    if (argc < 1)
    {
        cout << "Usage: " << argv[0] << " <Filename>" << endl;
        return 0;
    }
 
	//create board instance
	BBoard bb("Rica's Board");
	
	//setup the board with login/pass information, login, then run
	bb.setup(argv[1]);
	bb.login();
	bb.run();
	return 0;
}