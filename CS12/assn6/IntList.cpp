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
	//terminate if list is empty
	if (head == 0) return;

	for (IntNode *curr = head; curr != 0; curr = curr->next)
	{
		cout << curr->data;
		//only put a space if it's not the last node
		if (curr != tail)
		{
			cout << ' ';
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

//This function inserts a data value (within a new node) at the back end of the 
//list.
void IntList::push_back(int value)
{
	IntNode* newNode = new IntNode(value);
	if (head != 0)
	{
		tail->next = newNode;
		tail = newNode;
	}
	else
	{
		head = newNode;
		tail = newNode;
	}
}

/*This function removes the value (actually removes the node that contains the 
value) at the front end of the list. Do nothing if the list is already empty. 
In other words, do not call the exit function in this function as we did with 
the IntVector's pop_front.*/
void IntList::pop_front()
{
	//terminte if list is empty
	if (head == 0) return;
	
	IntNode* temp = head;
	head = head->next;
	delete temp;
		
	//if there are no elements, tail should point to 0
	if (head == 0)
	{
		tail = 0;
	}
}

//This function sorts the list into ascending order using the selection sort 
//algorithm.
void IntList::select_sort()
{	
	//terminate if list is empty
	if (head == 0) return;
	
	//initalize size of the current list
	int size = findSize();
	
	//pointer to the largest node
	IntNode* large = 0;
	//pointer to the previous node before the largest node
	IntNode* prevLarge = 0;
	
	//pointer to correct position in list for appending
	IntNode* end = 0;
	//prev node before the end node
	// IntNode* prevEnd = 0;
	
	//pos will iterate through the list until it reaches size - count
	int pos = 0;
	
	//controls entire seperator
	int count = 0;
	while (count < (size - 1))
	{
		//set largest node to default (head)
		large = head;
		//set end to default
		end = head;
		//node before largest one
		prevLarge = head;
		//node before the end of the li       
		
		// prevEnd = head;
		//reset pos
		pos = 0;
		
		//finds largest node
		for (IntNode *curr = head; 
			pos < (size - count); 
			curr = curr->next)
		{	
			if (curr->data > large->data)
			{
				large = curr;
			}
			pos++;
		}
		
		pos = 1;
		
		//finds node before largest node
		for (IntNode *curr = head; 
			pos < (size - count); 
			curr = curr->next)
		{	
			if (curr->next == large)
			{
				prevLarge = curr;
			}
			pos++;
		}
		
		pos = 0;
		
		//chooses correct position in list for appending
		for (IntNode * curr = head; 
			pos < (size - count); 
			curr = curr->next)
		{
			end = curr;
			pos++;
		}
		
		// pos = 1;
		
		// //chooses correct prev node before the end node
		// for (IntNode * curr = head; 
			// pos < (size - count); 
			// curr = curr->next)
		// {
			// if (curr->next == end)
			// {
				// prevEnd = curr;
			// }
			// pos++;
		// }
		
		//cout << "Run: " << count + 1 << endl;
		//cout << "\tLarge " << large->data << endl;
		//cout < 
		< "\tPrevLarge " << prevLarge->data << endl;
		//cout << "\tEnd " << end->data << endl;
		//cout << "\tPrevEnd " << prevEnd->data << endl;
		
		//checks if the last node is not the largest value (Otherwise do nothing)
		if (large != end)
		{
			//if appending to the end
			if (count == 0)
			{		
				IntNode* newNode = new IntNode(large->data);
				tail->next = newNode;
				tail = newNode;
				
				//delete old node
				//if deleting first node
				if (large == head)
				{
					pop_front();
				}
				//deleting a middle node
				else
				{
					IntNode* temp = large;
					prevLarge->next = large->next;
					large = 0;
					delete temp;
				}
			}
			//if appending to anything else other than the end
			else
			{
				//create a new node with the data
				IntNode* newNode = new IntNode(large->data);
				
				//appends new node
				newNode->next = end->next;
				end->next = newNode;
				
				//delete old node
				//if deleting first node
				if (large == head)
				{
					pop_front();
				}
				//deleting a middle node
				else
				{
					IntNode* temp = large;
					prevLarge->next = large->next;
					large = 0;
					delete temp;
				}
			}
		}
		count++;
		//cout << endl;
		//display();
		//cout << endl;
	}
}

/*This function assumes the values in the list are in sorted (ascending) order 
and inserts the data into the appropriate position in the list (so that the 
values will still be in ascending order after insertion). DO NOT call 
select_sort within this function.*/
void IntList::insert_sorted(int value)
{
	//will turn false and exit for loop if the right index in the nodelist is 
	//found
	bool notFound = true;
	//the new node with the value
	IntNode* newNode = new IntNode(value);
	
	//if list is empty, insert new value
	if (head == 0)
	{
		head = newNode;
		tail = newNode;
	}
	//if not, insert value in right position
	else
	{
		for (IntNode *curr = head; 
			curr != 0 && curr != tail && notFound; 
			curr = curr->next)
		{
			//check if value is the smallest
			if (value < curr->data)
			{
				push_front(value);
				notFound = false;
			}
			//if value is found, insert node
			else if (curr->next->data >= value)
			{
				newNode->next = curr->next;
				curr->next= newNode;
				notFound = false;
			}
		}
		//if pos still not found, append value at the end
		if (notFound)
		{
			tail->next = newNode;
			tail = newNode;
		}
	}
}

/*This function removes all values (actually removes the nodes that contain the 
value) that are duplicates of a value that already exists in the list. Always 
remove the later duplicate, not the first instance of the duplicate. DO NOT 
call select_sort within this function. This function does NOT assume the data 
is sorted.*/
void IntList::remove_duplicates()
{
	//terminte if list is empty
	if (head == 0) return;
	
	//holds possible deplicate of current node
	IntNode* dupe = 0;
	//points to the previous node before the dupe node
	IntNode* prev = head;
	
	for (IntNode *curr = head; curr != 0; curr = curr->next)
	{
		dupe = curr->next;
		prev = curr;
		while (dupe != 0)
		{
			if (curr->data == dupe->data)
			{
				//holds temporary node
				IntNode* temp = dupe;

				//if the duplicate is the last element, fix tail 
				if (dupe == tail)
				{
					dupe = 0;
					prev->next = 0;
					tail = prev;
					delete temp;	
				}
				else
				{				
					prev->next = dupe->next;
					dupe = dupe->next;
					delete temp;
				}
			}
			else
			{
				dupe = dupe->next;
				prev = prev->next;
			}
		}
	}
}

//PRIVATE//

//finds the size of the current node list
int IntList::findSize()
{
	int size = 0;
	for (IntNode *curr = head; curr != 0; curr = curr->next)
	{	
		size++;
	}
	return size;
}