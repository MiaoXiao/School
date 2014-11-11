#include <iostream>
#include "Date.h"
#include "Date.cpp"

using namespace std;

//TEST FUNCTIONS
void test1()
{
	cout << "1. Default" << endl; 

	Date x = Date(); 

	cout << "numeric:\t" ; 

	x.printNumeric(); cout << endl; 

	cout << "alpha:\t"; 

	x.printAlpha(); 

	cout << endl; 

	cout << "нннннннннннннннннннннннннн" << endl; 
}
void test2()
{
	cout << "2. Numeric Date: 7.3.1991" << endl; 

	Date x = Date(2,29,1503);

	cout << "numeric:\t" ; 

	x.printNumeric(); 

	cout << endl; 

	cout << "alpha:\t"; 

	x.printAlpha(); 

	cout << endl; 

	cout << "нннннннннннннннннннннннннн" << endl; 
}
void test3()
{
	cout << "3. Alpha Date: July 3, 1991" << endl; 

	Date x = Date("July",3,1991); 

	cout << "numeric:\t" ; 

	x.printNumeric(); 

	cout << endl;

	cout << "alpha:\t"; 

	x.printAlpha(); 

	cout << endl; 

	cout << "нннннннннннннннннннннннннн" << endl; 
}
void test4()
{
	cout << "4. Invalid Numeric Date: 0.3.1991 н> 1.3.1991" << endl; 

	Date x = Date(0,3,1991); 

	cout << "numeric:\t" ; 

	x.printNumeric(); 

	cout << endl; 

	cout << "alpha:\t"; 

	x.printAlpha(); 

	cout << endl; 

	cout << "нннннннннннннннннннннннннн" << endl; 
}
void test5()
{
	cout << "5. Invalid Alpha Date: 1.adf.1991 н> 1.1.2000" << endl; 

	Date x = Date("adf",1, 1991); 

	cout << "numeric:\t" ; x.printNumeric(); 

	cout << endl; 

	cout << "alpha:\t"; 

	x.printAlpha(); 

	cout << endl; 

	cout << "нннннннннннннннннннннннннн" << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	
	Date y(2, 1, 2003);
	
	y.printNumeric();
	cout << endl;
	
	Date x = y.addDays(-32);
	
	x.printNumeric();
	cout << endl;
	
	return 0;
}