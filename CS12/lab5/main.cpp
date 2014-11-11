#include <iostream>
#include "Distance.h"
#include "Distance.cpp"

using namespace std;

/*
d1: 0' 0"

d2: 2' 5.9"

d3: 0' 3.75"

d4: 6' 7.34"

d5: 8' 4"

d4 + d5: 14' 11.34"

d2 + d4: 9' 1.24"

d3 - d1: 0' 3.75"

d1 - d3: 0' 3.75"

d4 - d2: 4' 1.44"

d2 - d4: 4' 1.44"

d4 - d5: 1' 8.66"

d5 - d2: 5' 10.1"
*/

int main()
{
Distance d1;

 cout << "d1: ";

 d1.display(); cout << endl;

 Distance d2 = Distance(2, 5.9);

 Distance d3 = Distance(3.75);

 cout << "d2: "; d2.display(); cout << endl;

 cout << "d3: "; d3.display(); cout << endl;

 //test init helper function

 Distance d4 = Distance(5, 19.34);

 Distance d5 = Distance(100);

 cout << "d4: "; d4.display(); cout << endl;

 cout << "d5: "; d5.display(); cout << endl;

 //test add (<12 inches)

 cout << "d4 + d5: "; (d4 + d5).display(); cout << endl;

 //test add (>12 inches)

 cout << "d2 + d4: "; (d2 + d4).display(); cout << endl;

 //test sub (0 ft)

 cout << "d3 - d1: "; (d3 - d1).display(); cout << endl;

 //test sub (0 ft, negative conversion)

 cout << "d1 - d3: "; (d1 - d3).display(); cout << endl;

 //test sub (positive ft & inch)

 cout << "d4 - d2: "; (d4 - d2).display(); cout << endl;

 //test sub (negative ft & inch)

 cout << "d2 - d4: "; (d2 - d4).display(); cout << endl;

 //test sub (negative ft, positive inch)

 cout << "d4 - d5: "; (d4 - d5).display(); cout << endl;

 //test sub (positive ft, negative inch)

 cout << "d5 - d2: "; (d5 - d2).display(); cout << endl;

 //add more tests of your own ...

 return 0;
}