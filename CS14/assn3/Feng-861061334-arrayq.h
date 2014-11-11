//Name: Rica Feng
//ID: 861061334
//Date: 10/28/14
//Class: CS 14
//Assignment: PS3

#ifndef ARRAYQ_H
#define ARRAYQ_H

#include <iostream>
#include <cstddef>
#include <array>

template<typename T>

class arrayq 
{
	public:
		arrayq()
		{
			front = NULL;
			back = NULL;
			start = NULL;
			qsize = 0;
			qmemory = 0;
		}
		~arrayq()
		{
			delete[] front;
			front = NULL;
			back = NULL;
			start = NULL;
		}
		
		// should return the size (number of elements in the queue)
		int size() const 
		{
			return qsize;
		}

		// should place x in the queue at the tail.
		// if necessary, allocate more space
		void enqueue(const T &x) 
		{
			//check if memory has been allocated yet
			if (qmemory == 0)
			{
				start = new T[2];
				front = start;
				back = front;
				qmemory = 2;
			}
			//check if increased size will go over allocated memory
			//if so, then double memory and copy old elements to new
			if (back == front && qsize != 0)
			{
				//get position of front
				int position = 0;
				T *counter = start;
				while(counter != front)
				{	
					position++;
					counter++;
				}
				
				//keep track of old front and start pointer
				T *tempFront = front;
				T *tempStart = start;
				
				//init new start and front
				start = new T[qmemory * 2];
				front = start;
				
				int i = 0;
				for (i; i < qsize - position; i++)
				{
					start[i] = tempFront[i];
				}
				
				for (int j = 0; j < position; j++)
				{
					start[i] = tempStart[j];
					i++;
				}
				
				//put back  to element after last one
				back = start + i;
				
				qmemory = qmemory * 2;
				//std::cout << "Capacity increased to: ";
				//std::cout << qmemory << std::endl;
				
				delete[] tempStart;
			}

			qsize++;
			*back = x;
			//check if back wraps around
			if(back == start + (qmemory - 1))
			{
				//std::cout << "Back wraps around" << std::endl;
				back = start;
			}
			//only increment back if it is not equal to front
			else
			{
				//increment back
				back++;
			}
		}

		// should return the element at the head
		// if the queue is empty, return T{} (the default type T)
		T dequeue() 
		{
			//check if size is 0
			if(qsize == 0)
			{
				return T{};
			}
			
			T answer = *front;
			//move front to start if front is at the end of the array
			if(front == start + (qmemory - 1))
			{
				//std::cout << "Back = start" << std::endl;
				//front = start;
				//front loops around
				front = start;
			}
			else
			{
				//increment front normally
				front++;
			}
			qsize--;
			return answer;
		}
		
	private:
		// place any data members and any internal functions here
		T *back;
		T *front;
		T *start;
		int qsize;
		int qmemory;
};
#endif
