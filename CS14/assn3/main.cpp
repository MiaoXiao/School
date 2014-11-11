#include "arrayq.h"
#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(int argc ,char **argv) 
{
	arrayq <int> q;
	while(true) 
	{
		cout << "e = queue, d = dequeue, s = current size" << endl;
		char command;
		cin >> command;
		if(command == 'e'|| command =='E') 
		{
			int v;
			cout << "Enter an element to insert into queue: ";
			cin >> v;
			q.enqueue(v);
		}
		else if (command == 'd' || command == 'D') 
		{
			cout << "Element dequeued: ";
			int v = q.dequeue();
			cout << v << endl;
		}
		else if(command == 's'|| command == 'S')
		{
			cout << "Current size: ";
			cout << q.size() << endl;
		}
	}
}
