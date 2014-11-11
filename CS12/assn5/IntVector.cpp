#include <iostream>
#include <cstdlib>
#include "IntVector.h"

using namespace std;

//CONSTRUCTOR
/*This function should set both the size and capacity of the IntVector 
to 0 and will not allocate any memory to store integers 
(make sure you do not have a dangling (garbage) pointer).*/
IntVector::IntVector()
	:sz(0), cap(0), data(0){}
	
//CONSTRUCTOR
/*Sets both the size and capacity of the IntVector to the value of the 
parameter passed in and dynamically allocates an array of that size as 
well. (Don't forget to initialize all values in your array to 0.)*/
IntVector::IntVector(unsigned size)
	:sz(size), cap(size), data(new int[size])
{
	//fill allocated array with zeros
	fillArray(0);
}

//CONSTRUCTOR
/*Sets both the size and capacity of the IntVector to the value of the 
parameter passed in and dynamically allocates an array of that size as 
well. This function should initialize all elements of the array to the 
value of the 2nd parameter.*/
IntVector::IntVector(unsigned size, int value)
	:sz(size), cap(size), data(new int[size])
{
	//fill array with value
	fillArray(value);
}

//DECONSTRUCTOR
IntVector::~IntVector()
{
	delete[] data;
}

/*This function returns the current size (not the capacity) of the IntVector 
object, which is the value stored in the sz data field.*/
unsigned IntVector::size() const
{
	return sz;
}

/*This function returns the current capacity (not the size) of the IntVector 
object, which is the value stored in the cap data field.*/
unsigned IntVector::capacity() const
{
	return cap;
}

/*Returns whether the vector is empty (the sz field is 0).*/
bool IntVector::empty() const
{
	return (sz == 0);
}

/*This function will return the value stored in the element at the passed in 
index position. Your function should cause the program to exit if an index 
greater than or equal to the size is passed in. Because the index is an 
unsigned int (rather than just int) the compiler will not allow for a negative 
value to be passed in.*/
const int& IntVector::at(unsigned index) const
{
	if (index < sz)
	{
		return data[index];
	}
	exit(1);
}

/*This function will return the value stored at the element at the passed in 
index position. Your function should cause the program to exit (exit(1)) if an 
index greater than or equal to the sz is passed in. Because the index is an 
unsigned int (rather than just int) the compiler will not allow for a negative 
value to be passed in.*/
int& IntVector::at(unsigned index)
{
	if (index < sz)
	{
		return data[index];
	}
	exit(1);
}

/*
This function inserts data at location index. To do this, all values currently 
at position index and greater are shifted to the right by 1 (to the element 
right after its current position). Size is increased by 1. If size becomes 
larger than capacity, this function needs to double the capacity. 
In other words, if capacity and size are both 20 when this function is called, 
capacity will become 40 and size will be set to 21. Since other functions will 
also potentially need to expand (double) the capacity, implement the private 
helper function named expand (see above) to do this for you. This function 
should call exit(1) if an index value greater than sz is passed in.*/
void IntVector::insert(unsigned index, int value)
{
	//check if valid index
	if(index < sz)
	{
		sz += 1;
		if (sz > cap)
		{
			expand();
		}
		
		//move over every element after the index
		for (int i = sz; i > index; i--)
		{
			data[i - 1] = data[i - 2];
		}
		
		//finnaly insert value at index
		data[index] = value;
	}
	else
	{
		exit(1);
	}
}

/*This function removes the value at position index and shifts all of the values 
at positions greater than index to the left by one (to the element right before 
its current position). Size is decreased by 1. This function should call 
exit(1) if an index value greater than or equal to sz is passed in.*/
void IntVector::erase(unsigned index)
{
	//check if valid index
	if (index < sz)
	{
		sz -= 1;
		for (index; index < sz; index++)
		{
			data[index] = data[index + 1];
		}
	}
	else
	{
		exit(1);
	}
}

//This function will return the value stored in the first element.
const int& IntVector::front() const
{
	return data[0];
}

//This function will return the value stored in the first element.
int& IntVector::front()
{
	return data[0];
}

//This function will return the value stored in the last element.
const int& IntVector::back() const
{
	if (sz != 0)
	{
		return data[sz - 1];
	}
	return data[sz];
}

//This function will return the value stored in the last element.
int& IntVector::back()
{
	if (sz != 0)
	{
		return data[sz - 1];
	}
	return data[sz];
}

/*Assigns new content to the vector object, dropping all the elements contained 
in the vector before the call and replacing them by those specified by the 
parameters. The new value of size will be n and all values stored in the vector 
will have the value of the 2nd parameter.If the new value of size will be 
larger than capacity, then the capacity should be expanded by either 
doubling (expand()) or by increasing the capacity by a specific amount 
(expand(n - cap)), whichever*/
void IntVector::assign(unsigned n, int value)
{
	/*if n is less than or equal to cap*/
	if(n <= cap)
	{
		sz = n;
		fillArray(value);
	}
	//if new size is greater than cap
	else
	{
		if (cap >= (n - cap)) 
		{
			expand();
		}
		else
		{
			expand(n - cap);
		}
		sz = n;
		fillArray(value);
	}
}

/*This function inserts a value at the back end of the array.
Size is increased by 1. If size becomes larger than capacity, this function 
needs to double the capacity. In other words, if capacity and size are both 20 
when this function is called, capacity will become 40 and size will be set to 
21.Since other functions will also potentially need to expand (double) the 
capacity, implement the private helper function named expand (see above) to do 
this for you.*/
void IntVector::push_back(int value)
{
	//increase size and allocate new memory if needed
	sz += 1;
	if (sz > cap)
	{
		expand();
	}
		
	//append value to end of vector
	data[sz - 1] = value;
}

/*This function just needs to decrease size by 1.
This function should call exit(1) if pop_back is called on an empty vector.*/
void IntVector::pop_back()
{
	//exit if size is 0
	if (sz != 0)
	{
		sz -= 1;
	}
	else
	{
		exit(1);
	}
}

//This function reduces the size of the vector to 0.
void IntVector::clear()
{
	sz = 0;
}

/*This function resizes the vector to contain size elements.
If size is smaller than the current size(sz), this function just reduces the 
value of sz to size.If size is greater than the current size(sz), then the 
appropriate number of elements are inserted at the end of the vector, giving 
all of the new elements a value of 0.If the new value of size will be larger 
than capacity, then the capacity should be expanded by either doubling 
(expand()) or by increasing the capacity by a specific amount 
(expand(size - cap)), whichever results in the largest capacity.*/
void IntVector::resize(unsigned size)
{
	//if data needs to be allocated
	if (data == 0)
	{
		expand();
		fillArray(0);
	}
	
	//if new size is larger and is less than or equal to cap
	if(size > sz && size <= cap)
	{
		initValue(size, 0);
	}
	//if new size is larger and is greater than cap
	else if (size > sz && size > cap)
	{
		if (cap >= (size - cap)) 
		{
			expand();
		}
		else
		{
			expand(size - cap);
		}
		initValue(size, 0);
	}
	//if new size is smaller than sz. will also change sz accordingly.
	sz = size;
	
}

/*This function resizes the vector to contain size elements.
If size is smaller than the current size(sz), this function just reduces the 
value of sz to size.If size is greater than the current size(sz), then the 
appropriate number of elements are inserted at the end of the vector, giving 
all of the new elements the value passed in through the 2nd parameter (value).
If the new value of size will be larger than capacity, then the capacity should 
be expanded by either doubling (expand()) or by increasing the capacity by a 
specific amount (expand(size - cap)), whichever results in the largest 
capacity.*/
void IntVector::resize(unsigned size, int value)
{
	//if data needs to be allocated
	if (data == 0)
	{
		expand();
		fillArray(value);
	}
	
	//if new size is larger and is less than or equal to cap
	if((size > sz) && (size <= cap))
	{
		initValue(size, value);
	}
	//if new size is larger and is greater than cap
	else if ((size > sz) && (size > cap))
	{
		if (cap >= (size - cap)) 
		{
			expand();
		}
		else
		{
			expand(size - cap);
		}
		initValue(size, value);
	}
	//if new size is smaller than sz. will also change sz accordingly.
	sz = size;
}

/*This function requests that the capacity 
(the size of the dynamically allocated array) be set to n at 
minimum. This informs the vector of a planned increase in size, although notice 
that the parameter n informs of a minimum, so the resulting capacity may be any 
capacity equal or larger than this.This function should NOT ever reduce the 
size of the vector. If n is larger than the current capacity then the capacity 
should be expanded by either doubling (expand()) or by increasing the capacity 
by a specific amount (expand(n - cap)), whichever results in the largest 
capacity.In any case, a call to this function never affects the elements 
contained in the vector, nor the vector size.*/
void IntVector::reserve(unsigned n)
{
	//only expand if new cap is larger than cap
	if (n > cap)
	{
		if (cap >= (n - cap)) 
		{
			expand();
		}
		else
		{
			expand(n - cap);
		}
	}
	else if (n < cap)
	{
		exit(1);
	}
}


//PRIVATE//

//initalize entire array with value
void IntVector::fillArray(int value) const
{
	for (int i = 0; i < sz; i++)
	{
		data[i] = value;
	}
}

//init empty spots in vector with value until it reaches param(size)
void IntVector::initValue(unsigned size, int value)
{
	for(int i = sz; i < size; i++)
		{
			data[i] = value;
		}
}

/*This function will double the capacity of the vector. This function should 
reallocate memory for the dynamically allocated array and update the value of 
capacity.Make sure you don't create a memory leak here.*/
void IntVector::expand()
{
	if (cap != 0 && sz != 0)
	{
		//double the capacity
		cap *= 2;
		//init new pointer to hold array
		int* temp = new int[cap];
	
		//move all of old data to temp
		for (int i = 0; i < sz; i++)
		{
			temp[i] = data[i];
		}
		
		//delete elements in data, then move temp to data
		delete[] data;
		data = temp;
	}
	else
	{
		//unless cap and sz is 0
		cap = 1;
		sz = 1;
		
		//if data is not allocated yet
		if (data == 0)
		{
			data = new int[1];
		}
	}
}

/*This function will expand the capacity of the vector by amount passed in. 
This function should reallocate memory for the dynamically allocated array and 
update the value of capacity.Make sure you don't create a memory leak here.*/
void IntVector::expand(unsigned amount)
{
	if (cap != 0 && sz != 0)
	{
		//increase cap by amount
		cap += amount;
		//init new pointer to hold array
		int* temp = new int[cap];
	
		//move all of old data to temp
		for (int i = 0; i < sz; i++)
		{
			temp[i] = data[i];
		}
		
		//delete elements in data, then move temp to data
		delete[] data;
		data = temp;
	}
	else
	{
		//unless cap and sz is 0
		cap = 1;
		sz = 1;
		
		//if data is not allocated yet
		if (data == 0)
		{
			data = new int[1];
		}
	}
}