#include <iostream>
#include "Distance.h"

using namespace std;

/////PUBLIC/////

//Default constructor that constructs a length of 0 (0 feet and 0 inches).
/*Distance::Distance()
{
	feet = 0;
	inches = 0.0;
}

//Constructs a length of ft feet and inch inches, unless inch >= 12.0, 
	//in which case the values of feet and inches are adjusted accordingly.
Distance::Distance(unsigned f, double i)
{
	feet = f;
	inches = i;
	init();
}

//Constructs a length of inch inches, correctly converted to feet and inches.
Distance::Distance(double i)
{
	feet = 0;
	inches = i;
	init();
}*/

//member function that returns the distance in all inches – 
	//does not change the state of the object.
double Distance::convertToInches() const
{
	double tFeet = feet;
	double tInches = inches;
	while (tFeet > 0)
	{
		tFeet--;
		tInches += 12.0;
	}
	return tInches;
}

//- add (+): the sum of two Distances;
const Distance Distance::operator+(const Distance &a) const
{
	Distance sum;
	
	sum.feet = feet + a.feet;
	sum.inches = inches + a.inches;
	
	while (sum.inches >= 12.0)
	{
		sum.feet++;
		sum.inches -= 12.0;
	}
	
	return sum;
}

//- subtract(-): the difference between two Distances
const Distance Distance::operator-(const Distance &a) const
{
	Distance difference;
	
	//salesEurope.dollars > salesAsia.dollars || salesEurope.dollars == salesAsia.dollars && salesEurope.cents > salesAsia.cents
	//check if feet > a.feet
	if (feet > a.feet || feet == a.feet && inches > a.inches)
	{
		difference.feet = feet - a.feet;
		difference.inches = inches - a.inches;
	}
	//else a.feet > feet
	else
	{
		difference.feet = a.feet - feet;
		difference.inches = a.inches - inches;
	}

	while (difference.inches < 0)
	{
		difference.feet--;
		difference.inches += 12.0;
	}
	
	return difference;
}
//FOR OPERANTS
//always be a proper Distance object, i.e. a positive distance, no 
//matter what order the operands are in

//outputs to standard output (cout) the Distance in the 
	//format: feet' inches" (e.g.: 3' 4.25")
void Distance::display() const
{
	cout << feet << "' " << inches << "\"" << endl;
}

/////PRIVATE/////

//used by the initializing constructors to properly initialize a positive length 
	//and convert inches >= 12 to feet.
void Distance::init()
{
	while (inches >= 12.0)
	{
		feet++;
		inches -= 12.0;
	}
}