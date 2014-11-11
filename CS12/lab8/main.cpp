#include <iostream>
#include "IntList.cpp"

using namespace std;

int main()
{
	IntList ls;
	//ls.push_front(5);
	ls.push_front(3);
	ls.push_front(6);
	ls.push_front(6);
	ls.push_front(5);
	ls.push_front(6);
	ls.push_front(6);
	ls.push_front(2);
	ls.push_front(-1);
	ls.display();
	ls.pop_front();
	cout << endl;
	ls.display();
	return 0;
}