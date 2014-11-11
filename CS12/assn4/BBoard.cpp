#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BBoard.h"

//PUBLIC//

//constructor that creates a board with a default title, empty user & 
//message lists, and the "default" User
BBoard::BBoard()
{
	title = "Rica's Board!";
	user_list.clear();
	current_user = User();
	message_list.clear();
}

//same as default constructor, except that it sets the title of the board.
BBoard::BBoard(const string &ttl)
{
	title = ttl;
	user_list.clear();
	current_user = User();
	message_list.clear();
}

//imports all the authorized users from an input file, storing them as User 
//objects in the vector user_list The name of the input file is passed in as a 
//parameter to this function.
void BBoard::setup(const string &input_file)
{
	string u, p;
	bool notEnd = true;
	ifstream allUsers;
	
	allUsers.open(input_file.c_str());
	
	while (notEnd)
	{
		allUsers >> u;
		if (u != "end")
		{
			allUsers >> p;
			add_user(u, p);
		}
		else
		{
			notEnd = false;
		}
	}
	allUsers.close();
}

/*asks for and validates current user/password
This function asks for a username and password, and checks the user_list vector
 for a matching User.
This function must take in both username and password (even if the username 
doesn't exist, ie password is always requested), unless username is “q” or “Q”, 
in which case quit.
If a match is found, it sets current_user to the identified User from the list.
If not, it will keep asking until a match is found or the user types: "q" or "Q" 
as the username.
You can assume we do not have a member with name "q" or "Q". When the user 
chooses to quit, say "Bye!" and call "exit(0)" (see cstdlib reference) command 
to exit the program.
Read output specifications for details.*/
void BBoard::login()
{
	string user, pass;
	bool notValidUser = true;
	
	//welcome message
	cout << "Welcome to " << title << endl;
	
	//will keep looping unless terminated with q/Q or when valid user and pass
	//is inputted
	do
	{
		cout << "Enter your username (\"Q\" or \"q\" to quit): ";
		cin >> user;
		
		if (user == "Q" || user == "q")
		{
			cout << "Bye!" << endl;
			exit(0);
		}
		
		cout << "Enter your password: ";
		cin >> pass;
		
		if(user_exists(user, pass))
		{	
			current_user = get_user(user);
			notValidUser = false;
		}
		else
		{
			cout << "Invalid Username or Password!" << endl << endl;
		}
	} while(notValidUser);
}

/*This function contains the main loop of the BBoard.
Note: if login() has not set a valid current_user, this function must abort 
without showing the menu - i.e. there must be no way to get around 
logging in!
Question: how will you know if a valid user is not logged in?
In the main loop, you should display the following menu items:
"Display Messages ('D' or 'd'), "Add New Message('N' or 'n')", and "Quit ('Q' or 
'q')".
If the user selects one of these menu items, the corresponding method of BBoard 
should be invoked; with any other input, the user should be asked to try again.
'Q'/'q' should terminate the program by invoking exit(0), as described for 
login. See suggested private functions for details.*/
void BBoard::run()
{
	//greetings
	cout << "Welcome back " << current_user.get_username() << "!" << endl;
	cout << endl;
	
	//holds user input
	string action;
	
	//will become false when terminating
	bool notTerminate = true;
	
	//if action is set to Q or q, quit program
	while(notTerminate)
	{
		//MAIN MENU
		cout << "Menu" << endl;
		cout << "  - Display Messages (\'D\' or \'d\')" << endl;
		cout << "  - Add New Message (\'N\' or \'n\')" << endl;
		cout << "  - Quit (\'Q\' or \'q\')" << endl;
		cout << "Choose an action: ";
		cin >> action;
		
		//Display message
		if (action == "D" || action == "d")
		{
			display();
		}
		//Add new message
		else if (action == "N" || action == "n")
		{
			add_message();
		}
		//Quit
		else if (action == "Q" || action == "q")
		{
			cout << "Bye!";
			notTerminate = false;
		}
		else
		{
			notTerminate = false;
		}
		cout << endl;
	}
	
}

//PRIVATE//

//This function can be called from the setup function to add the users from file to 
//user_list.
void BBoard::add_user(const string &name, const string &pass)
{
	user_list.push_back(User(name, pass));
}

//Checks if the username/password combination matches any of the Users in the 
//user_list. Returns true if a match is found, false otherwise. 
//Useful for login function.
bool BBoard::user_exists(const string &name, const string &pass) const
{
	for (unsigned int count = 0; count < user_list.size(); count++)
	{
		if (user_list.at(count).check(name, pass))
		{
			return true;
		}
	}
	return false;
}

//Returns the User with the given name. This function can be used by login() to 
//set the current_user only if a valid match has been found by user_exists.
//There must be no other way to set current_user to anything other than its 
//initial value (the default User - see User class)
User BBoard::get_user(const string &name) const 
{
	for (unsigned int count = 0; count < user_list.size(); count++)
	{
		if (user_list.at(count).get_username() == name)
		{
			return user_list.at(count);
		}
	}
	return user_list.at(0);
}

//This function would be used by the interface function run. It displays all messages 
//in message_list.
//The output must be formatted exactly as in the example below.
void BBoard::display() const 
{
	cout << endl;
	//if there is at least 1 message, continue on with functions
	if (message_list.size() == 0)
	{
		
		cout << "Nothing to Display." << endl;
	}
	else
	{
		//iterate through message list and display all
		for (unsigned int count = 0; count < message_list.size(); count++)
		{
			cout << "-----------------------------------------------" << endl;
			cout << "Message #" << count + 1 << ": ";
			message_list.at(count).display();
		}
		cout << "-----------------------------------------------" << endl;
	}
}

//This function would be used by the interface function run. It asks the user to input 
//a message. Every message includes a subject line and a message line (both are 
//single lines, so you can ignore newlines). e.g.,
void BBoard::add_message() 
{
	string subject, body;

	cout << endl;
	cout << "Subject: ";
	cin.ignore();
	getline(cin, subject);
	
	cout << "Body: ";
	getline(cin, body);
	
	//init message instance and its author, subject, and body
	Message record = Message(current_user.get_username(), subject, body);
	
	//push back message class to vector
	message_list.push_back(record);
	
	cout << "Message recorded!" << endl;
}