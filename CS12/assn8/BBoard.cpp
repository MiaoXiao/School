//  =============== BEGIN ASSESSMENT HEADER ================
/// @file assn8/BBoard.cpp
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
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "BBoard.h"
#include "User.h"
#include "Topic.h"
#include "Reply.h"
#include "Message.h"


//PUBLIC//

//constructor that creates a board with a default title, empty user & 
//message lists, and the "default" User
BBoard::BBoard()
{
	title = "Rica's Board!";
	user_list.clear();
	current_user = 0;
	message_list.clear();
}

//same as default constructor, except that it sets the title of the board.
BBoard::BBoard(const string &ttl)
{
	title = ttl;
	user_list.clear();
	current_user = 0;
	message_list.clear();
}

//deconstructor
BBoard::~BBoard()
{
	for(int i = 0; i < message_list.size(); i++)
	{
		delete message_list[i];
	}
}

//imports all the authorized users from an input file, storing them as User 
//objects in the vector user_list The name of the input file is passed in as a 
//parameter to this function.
void BBoard::load_users(const string &userfile)
{
	string u, p;
	bool notEnd = true;
	ifstream allUsers;
	
	allUsers.open(userfile.c_str());
	
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

//IMPLEMENT
/*
This function gets a filename (datafile) of a file that stores the messages 
from previous sessions in the given format (See File Format Specs).
It opens and reads the file, creating Topic and Reply objects as appropriate, 
and fills the message_list vector (note: remember that message_list is a vector 
of pointers, not messages).If an error occurs when opening the file, it 
returns false. Returns true otherwise.

EXAMPLE:

1
<begin_topic>
:id: 1
:subject: CS12 Assignment 7
:from: messi
:children: 6 9
:body: The assignment is hard so go step by step.
You can read the Tips & Tricks part for some help.
Has anyone started already?
<end>
*/
bool BBoard::load_messages(const string& datafile)
{
	//number of messages in files
	int maxMessage;
	//keep count of amount of messages
	int count = 0;
	
	//holds specific keyword strings
	string keyword;
	
	//type of message (topic or reply)
	//also category
	vector <string> message;
	string messageType;
	
	//hold ids
	vector <int> id;
	int tempid;
	
	//hold subjects
	vector <string> subject;
	string tempSubject;
	string finalSubject;
	
	//holds authors
	vector <string> author;
	string tempAuthor;
	
	//hold vector of child ids inside children vector
	vector <string> child;
	string tempChild;
	string stringChild;
	string finalChild = "";
	int intChild;
	ostringstream ss;
	
	//holds bodies
	vector <string> body;
	string tempBody = "";
	string finalBody = "";
	
	//open stream
	ifstream loadFile;
	loadFile.open(datafile.c_str());
	
	//check if file is opened correctly
	if (!loadFile.is_open()) 
	{
		cout << "Could not open file" << endl;
		return false;
	}
	
	//stream in number of messages
	loadFile >> maxMessage;
	
	while (count < maxMessage)
	{
		//stream message type and verify specific message type
		loadFile >> messageType;
		message.push_back(messageType);
		
		//id
		loadFile >> keyword;
		loadFile >> tempid;
		id.push_back(tempid);
		
		//subject
		loadFile >> keyword;
		loadFile >> finalSubject;
		do
		{
			loadFile >> tempSubject;
			if(tempSubject != ":from:")
			{
				finalSubject += " " + tempSubject;
			}
			
		} while(tempSubject != ":from:");
		subject.push_back(finalSubject);
	
		
		//author
		loadFile >> tempAuthor;
		author.push_back(tempAuthor);

		
		loadFile >> keyword;
		
		//child
		//next keyword might be children, if not, skip children
		// if (keyword == ":children:")
		// {
			// while(loadFile >> keyword)
			// {
				
				// ss << intChild;
				// finalChild += ss.str() + " ";
				
				// loadFile >> keyword;
			// }
			// child.push_back(finalChild);
		
		
		// else
		// {
			// child.push_back("empty");
		// }

		
		//body
		loadFile >> finalBody;
		do
		{	
			loadFile >> tempBody;
			if(tempBody != "<end>")
			{
				finalBody += " " + tempBody;
			}
		}while(tempBody != "<end>");
		
		body.push_back(finalBody);

		//will end if count exceeds size of maxMessages
		count++;
	}
	
	for (int i = 0; i < maxMessage; i++)
	{	
		if (message.at(i) == "<begin_topic>")
		{
			Topic* pTopic = new Topic(author.at(i), subject.at(i), body.at(i), id.at(i));
			message_list.push_back(pTopic);
		}
		else
		{
			// Reply* pReply = new Reply(author.at(i), subject.at(i), body.at(i), id.at(i));
			// message_list.push_back(pReply);
		}
	}
	
	loadFile.close();
	return true;
}

//IMPLEMENT
/*
This is the final action of the bulletin board before closing:
It gets a filename (datafile) of a file that will store all of the the messages, 
and after opening the file writes the messages into it with the same format 
(See File Format Specs).
If an error occurs when opening the file, it returns false. Returns true 
otherwise.(Note: Since you will be opening the file for writing - i.e. an 
ofstream - "file not found" is NOT an error; a new file will simply be 
created for you).
*/
bool BBoard::save_messages(const string& datafile)
{
	ofstream saveFile;
	saveFile.open(datafile.c_str());
	
	//check if file is opened correctly
	 if (!saveFile.is_open()) 
	{
		cout << "Could not open file" << endl;
		return false;
	}
	
	//if no messages, do nothing
	if (message_list.size() == 0) return false;
	
	//add number of messages to stream
	saveFile << message_list.size() << "\n";
	
	for (int i = 0; i < message_list.size(); i++)
	{
		saveFile << message_list.at(i)->to_formatted_string();
		saveFile << '\n';
	}
	
	saveFile.close();
	return true;
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
		
		if(get_user(user, pass) != 0)
		{	
			current_user = get_user(user,pass);
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
	cout << "Welcome back " << current_user->get_username() << "!" << endl;
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
		cout << "  - Add New Topic (\'N\' or \'n\')" << endl;
		cout << "  - Add Reply to a Topic (\'R\' or \'r\')" << endl;
		cout << "  - Quit (\'Q\' or \'q\')" << endl;
		cout << "Choose an action: ";
		cin >> action;
		
		//Display message
		if (action == "D" || action == "d")
		{
			display();
		}
		//Add new topic
		else if (action == "N" || action == "n")
		{
			add_topic();
		}
		//add new reply
		else if (action == "R" || action == "r")
		{
			add_reply();
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
/*
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
*/

//Returns the User with the given name. This function can be used by login() to 
//set the current_user only if a valid match has been found by user_exists.
//There must be no other way to set current_user to anything other than its 
//initial value (the default User - see User class)
const User* BBoard::get_user(const string &name, const string &pw) const 
{
	for (unsigned int i = 0; i < user_list.size(); i++)
	{
		//if user and pass matches the user and pass in file, return current
		//user
		if (user_list.at(i).check(name, pw))
		{
			return &user_list.at(i);
		}
	}
	//return null if not found
	return 0;
}

//FIX ME
//This function would be used by the interface function run. It displays all messages 
//in message_list.
//The output must be formatted exactly as in the example below.
void BBoard::display() const 
{
	cout << endl;
	//if there is at least 1 message pointer, continue on with functions
	if (message_list.size() == 0)
	{
		cout << "Nothing to Display." << endl;
	}
	else
	{
		//iterate through message list but only display topics
		for (unsigned int i = 0; i < message_list.size(); i++)
		{
			
			//check if message is topic
			if (message_list.at(i)->is_reply() == false)
			{
				cout << "-------------------------------------------------------------------------------" << endl;
				//how to handle indents?
				message_list.at(i)->print(0);
			}
		}
		cout << "-------------------------------------------------------------------------------" << endl;
	}
}

//This function would be used by the interface function run. It asks the user to input 
//a message. Every message includes a subject line and a message line (both are 
//single lines, so you can ignore newlines). e.g.,
/*
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
*/


/*
This function asks the user to create a new Topic (i.e. the first message of a new 
discussion "thread"). Every Topic includes a subject (single line), and a body that may consist of 
multiple lines. e.g.,

Subject: "Thanks"
Body: "I would like to thank you for this awesome board.
 I'll visit here regularly."
 
The body ends when the user enters an empty line (i.e. a "double enter"). Each Topic also stores 
the username of current_user; and a message id, which is (index of its Message* + 1)
For example, the first message on the board will be a Topic whose pointer will be stored at index 0 
of the message_list vector, so its message id will be (0 + 1) = 1
(there are better ways of establishing unique ids for a set of objects, but for now this will work fine)
Once the Topic has been constructed, a pointer to it is added to message_list. 
Hint: Do you need pointers to automatic or dynamic Topics?
*/
void BBoard::add_topic()
{
	//holds subject
	string subject;
	//append all bodies here to make complete message
	string finalBody = "";
	
	cout << endl;
	cout << "Subject: ";
	cin.ignore();
	getline(cin, subject);
	
	//if user presses enter twice, continue with program
	cout << "Body: ";
	create_body(finalBody);
	
	//init topic instance and its author, subject, body, and id
	//make pointer to point to that topic
	//Topic record(current_user->get_username(), subject, finalBody, message_list.size() + 1);
	Topic* pTopic = new Topic(current_user->get_username(), subject, finalBody, message_list.size() + 1);
	
	//push back pointer to message class to vector
	message_list.push_back(pTopic);
	
	cout << "Message recorded!" << endl;
}

//IMPLEMENT
/*This function asks the user to enter a reply to a given Message (which may be either a Topic or a 
Reply, so we can handle nested replies).
The add_reply function first asks the user for the id of the Message to which they are replying; if 
the number provided is greater than the size of message_list it should output an error message 
and loop back, continuing to ask for a valid Message id number until the user enters either -1 (or 
any negative number, to return to the menu); or a valid id.
If the id is valid, then the function asks for the body of the new message, and constructs the Reply, 
pushing back a pointer to it on the message_list
The subject of the Reply is a copy of the parent Topic's subject with the "Re: " prefix.

e.g., suppose the subject of message #9 was "Thanks", and a user is replying to that message:
Enter Message ID: 9
Body: It was a pleasure implementing this.
 I hope everyone likes it. 
Note: As before, the body ends when the user enters an empty line.

The above dialog will generate a reply that has "Re: Thanks" as its subject and "It was a pleasure 
implementing this.\nI hope everyone likes it." as its body.

How will we know what Topic this is a reply to?
In addition to keeping a pointer to every Message (whether Topic or Reply) in BBoard's 
message_list vector, every Message (whether Topic or Reply) will also store a vector of pointers to 
all its own Replies.
So whenever we build a Reply, we must immediately store a pointer to it inside its parent 
Message. Therefore, you will:
1. create a "polymorphic" dynamic Reply with the input data, setting its subject to "Re: " + its 
parent's subject (this is handled inside Reply's constructor);
2. call the add_child function on the parent message to push_back the Message* (to the 
new Reply) to the parent's child_list vector;
3. Finally, push_back the same pointer to BBoard's message_list.
Note: When the user chooses to return to the menu, do not call run() again - just invoke return;
*/
void BBoard::add_reply()
{
	int id;
	string finalBody = "";
	bool notValidID = true;
	
	while (notValidID)
	{
		cout << endl;
		cout << "Enter Message ID (-1 for Menu): ";
		cin >> id;
		
		if (id > message_list.size())
		{
			cout << "Invalid Message ID!!" << endl;
		}
		else
		{
			//id may be valid, or -1 or lessng
			notValidID = false;
		}
		if (id <= -1)
		{
			notValidID = false;
		}
	}
	
	//if id is a valid id, continue with reply
	//otherwise, id will be negative, so quit
	if (id >= 1)
	{
		cout << "Enter Body: ";
		//checks if two returns are pressed
		cin.ignore();
		create_body(finalBody);
		
		//constuct reply
		// Reply* pReply = new Reply(current_user->get_username(), message_list.at(id - 1)->get_subject(), finalBody, id);
		// message_list.at(id - 1)->add_child(pReply);
		// message_list.push_back(pReply);
	}
	
	cout << "Message recorded!" << endl;
}

void BBoard::create_body(string &finalBody)
{
	//checks if two returns are pressed
	bool repeat = true;
	//temporoary body string, will later append to finalBody
	string body = "";
	
	do
	{
		getline(cin, body);
		if (body.empty())
		{
			finalBody.resize(finalBody.size() - 1);
			repeat = false;
		}
		else
		{
			finalBody += body + '\n';
		}
	}while(repeat);
}