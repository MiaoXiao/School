#include <iostream>
#include "IntList.h"

using namespace std;

//Always, for EVERY function you implement test the special cases:

//Here are some:
// - empty list
// - list of size 1 (1 Node) Is it going down to an empty list?
// - working with front of list
// - working with back of list

//CONSTRUCTOR
//Initialize an empty list.
IntList::IntList(): head(0),tail(0) {}

//DECONSTRUCTOR
//This function should deallocate all remaining dynamically allocated memory 
//(all remaining IntNodes).
IntList::~IntList()
{
	while (head != 0)
	{
		pop_front();
	}
}

/*This function displays to a single line all of the int values stored in the 
list, each separated by a space. It should NOT output a newline or space at the
end.*/
void IntList::display() const
{
	if (head != 0)
	{
		for (IntNode *curr = head; curr != 0; curr = curr->next)
		{
			cout << curr->data;
			//only put a space if its not the last node
			if (curr != tail)
			{
				cout << ' ';
			}
		}
	}
}

//This function inserts a data value (within a new node) at the front end of 
//the list.
void IntList::push_front(int value)
{
	IntNode* temp = new IntNode(value);
	temp->next = head;
	head = temp;
	
	//check if there is only 1 node, if so point tail to node
	if (tail == 0)
	{
		tail = temp;
	}
}

/*This function removes the value (actually removes the node that contains the 
value) at the front end of the list. Do nothing if the list is already empty. 
In other words, do not call the exit function in this function as we did with 
the IntVector's pop_front.*/
void IntList::pop_front()
{
	if (head != 0)
	{
		IntNode* temp = head;
		head = head->next;
		delete temp;
		
		//if there are no elements, tail should point to 0
		if (head == 0)
		{
			tail = 0;
		}
	}
}