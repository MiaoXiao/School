#include <iostream>
#include "IntList.h"

using namespace std;

//test int list push front
void testPush_front(IntList& ls)
{
	cout << "Push front: 4" << endl;
	ls.push_front(4);
	ls.display();
	
	cout << endl << "Push front: 2, 1" << endl;
	//ls.push_front(3);
	ls.push_front(2);
	ls.push_front(1);
	ls.display();
	
	cout << endl;
}

//test int list push back
void testPush_back(IntList& ls)
{
	cout << "Push back: 7" << endl;
	ls.push_back(7);
	ls.display();
	cout << endl;
	
	cout << "Push back: 1, 2, 3, 4" << endl;
	ls.push_back(1);
	ls.push_back(2);
	ls.push_back(3);
	ls.push_back(4);
	ls.display();
	cout << endl;
}

//test select sort
void testSelect_sort(IntList& ls)
{
	cout << "Sort" << endl;
	ls.select_sort();
	ls.display();
	cout << endl;
}

//test insert sort
void testInsert_sorted(IntList& ls)
{
	cout << "Insert 3 in order" << endl;
	ls.insert_sorted(3);
	ls.display();
	cout << endl;

	cout << "Insert 5 in order" << endl;
	ls.insert_sorted(5);
	ls.display();
	cout << endl;
	
	cout << "Insert 8 in order" << endl;
	ls.insert_sorted(8);
	ls.display();
	cout << endl;
	
	cout << "Insert 6 in order" << endl;
	ls.insert_sorted(6);
	ls.display();
	cout << endl;
	
	cout << "Insert 0 in order" << endl;
	ls.insert_sorted(0);
	ls.display();
	cout << endl;
}

//test remove duplicates
void testRemove_duplicates(IntList& ls)
{
	cout << "Remove duplicates" << endl;
	ls.remove_duplicates();
	ls.display();
	cout << endl;
}

int main()
{
	IntList ls;
	
	//testPush_front(ls);
	testPush_back(ls);
	testSelect_sort(ls);
	testInsert_sorted(ls);
	//testPush_back(ls);
	//testPush_front(ls);
	//testRemove_duplicates(ls);
	return 0;
}