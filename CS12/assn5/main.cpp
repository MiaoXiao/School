#include <iostream>
#include <vector>
#include "IntVector.h"

using namespace std;

void testValues(IntVector& test)
{
	cout << "Size: " << test.size() << endl;
	cout << "Capacity: " << test.capacity() << endl;
	cout << "Array: " << endl;
	
	//display array if vector is NOT empty
	if (!test.empty())
	{
		for (int i = 0; i < test.size(); i++)
		{
			cout << "#" << i << ": " << test.at(i);
			cout << endl;
		}
	}
	else
	{
		cout << "Vector is empty!" << endl;
	}
	cout << endl;
}

void testPush_Back(IntVector& test)
{
	cout << "ORIGINAL" << endl;
	testValues(test);
	
	for (int i = 0; i < 5; i++)
	{
		cout << "Push back " << i << endl;
		test.push_back(i);
		testValues(test);
	}
}

void testPop_Back(IntVector& test)
{
	for (int i = 0; i < 3; i++)
	{
		test.pop_back();
		cout << "Popback" << endl;
		testValues(test);
	}
}

void testAt(IntVector& test)
{
	cout << "First position" << endl;
	cout << test.at(0) << endl << endl;
	cout << "Last position" << endl;
	cout << test.at(test.size() - 1) << endl << endl;
	cout << "Front position" << endl;
	cout << test.front() << endl << endl;
	cout << "Back position" << endl;
	cout << test.back() << endl << endl;
	
	cout << "First pos changed to last pos" << endl;
	test.at(0) = test.back();
	testValues(test);
}

void testAssign(IntVector& test)
{
	cout << "Size of 3, all 0" << endl;
	test.assign(3, 0);
	testValues(test);
	
	cout << "Size of 3, all 3" << endl;
	test.assign(3, 3);
	testValues(test);
	
	cout << "Size of 10, all 5" << endl;
	test.assign(10, 5);
	testValues(test);
	
	cout << "Size of 17, all 5" << endl;
	test.assign(17, 5);
	testValues(test);
	
	//cout << "Size of 64, all 5" << endl;
	//test.assign(64, 5);
	//testValues(test);
	
	cout << "Size of 65, all 5" << endl;
	test.assign(65, 5);
	testValues(test);
}

void testInsert(IntVector& test)
{
	cout << "At pos 2, insert 0" << endl;
	test.insert(2, 0);
	testValues(test);
	
	cout << "At pos 5, insert 0" << endl;
	test.insert(5, 0);
	testValues(test);
	
	cout << "At pos 6, insert 0" << endl;
	test.insert(6, 0);
	testValues(test);
	
	cout << "At pos 0, insert 1" << endl;
	test.insert(0, 1);
	testValues(test);
}

void testErase(IntVector& test)
{
	cout << "Erase pos 1" << endl;
	test.erase(1);
	testValues(test);

	cout << "Erase pos 2" << endl;
	test.erase(2);
	testValues(test);
	
	cout << "Erase pos 3" << endl;
	test.erase(3);
	testValues(test);
}

void testResize(IntVector& test)
{
	cout << "Resize to 5 " << endl;
	test.resize(5);
	testValues(test);
	
	cout << "Resize to 10 " << endl;
	test.resize(10);
	testValues(test);
	
	cout << "Resize to 16 " << endl;
	test.resize(16);
	testValues(test);
	
	cout << "Resize to 5, fill 1 " << endl;
	test.resize(5, 1);
	testValues(test);
	
	cout << "Resize to 10, fill 1 " << endl;
	test.resize(10, 1);
	testValues(test);
	
	cout << "Resize to 17, fill 1 " << endl;
	test.resize(17, 1);
	testValues(test);
}

void testReserve(IntVector& test)
{
	//cout << "Expand to 7(Exits)" << endl;
	//test.reserve(7);
	//testValues(test);

	cout << "Expand to 8" << endl;
	test.reserve(8);
	testValues(test);
	
	cout << "Expand to 16" << endl;
	test.reserve(9);
	testValues(test);
	
	cout << "Expand to 33" << endl;
	test.reserve(33);
	testValues(test);
	
	//cout << "Expand to 32" << endl;
	//test.reserve(32);
	//testValues(test);
}

void testVector()
{
	vector<int> v;

	v.push_back(100);

	cout << v.size() << " : " << v.capacity() << endl;
}

int main()
{
	//test default constructor (everything 0)
	IntVector test;
	
	//test 1 param constructor (size)
	//IntVector test(0);
	
	//test 2 param constuctor (size, value in array)
	//IntVector test(1, 0);
	
	//TESTS
	
	//testVector();
	//testPush_Back(test);
	//testReserve(test);
	//testResize(test);
	//testInsert(test);
	//testErase(test);
	//testAssign(test);
	//testAt(test);
	//testPop_Back(test);
	
	return 0;
}