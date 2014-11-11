#include <iostream>

using namespace std

/*This function generates a random double value between a and b*/
double randFloat(double a, double b)
{
 return a + (static_cast<double>(rand()) / RAND_MAX) * (b - a);
}

//theoretical mean equation
double tMean(double a, double b)
{
	return (a + b) / 2;
}

//theoretical variance equation
double tVariance(double a, double b)
{
	return (b - a) * (b - a) / 12;
}

int main()
{

	return 0;
}