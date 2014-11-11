#include <iostream>
#include "Message.h"

//displays the message in the given format. See output specs.
void Message::display() const
{
	cout << subject << endl;
	cout << "from " << author << ": " << body << endl;
}