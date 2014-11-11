#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message
{
private:
	string author;
	string subject;
	string body;
public:
	//default constructor
	Message()
		:author(""), subject(""), body(""){}
	//Constructor with parameters
	Message(const string &athr, const string &sbjct, const string &body)
		:author(athr), subject(sbjct), body(body){}
	void display() const;
};

#endif