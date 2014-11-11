#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

//arrays for storing doubles
double smallArray[500];
double largeArray[500];

//global constants to define ranges for number generator
const double SMALLA = -3.0,SMALLB = 3.0;
const double LARGEA = -7.0,LARGEB = -1.0;

//This function generates a random double value between a and b
double randFloat(double a, double b)
{
	return a + (static_cast<double>(rand()) / RAND_MAX) * (b - a);
}

//computes thearetical mean of array
double tMean(double a, double b)
{
	return (a + b) / 2.0;
}

//computes practical mean of array
double pMean(double array[], double size)
{
	//holds collective sum for for finding mean
	double sum = 0;
	for (int count = 0; count < size; count++)
	{
		sum = sum + array[count];
	}
	return sum / size;
}

//computes thearetical variance of array
double tVariance(double a, double b)
{
	return (b - a) * (b - a) / 12.0;
}

//computes practical variance of array
double pVariance(double array[], double size, double mean)
{
	//holds collective sum for finding variance
	double sum = 0;
	for (int count = 0; count < size; count++)
	{
		sum = sum + (array[count] - mean) * (array[count] - mean);
	}
	return sum / size;
}

//fills array with numbers between 4 and 10
void fillArray(double array[], int size, double a, double b)
{
	for (int count = 0; count < size; count++)
	{
		//uses randFloat to generate numbers between 4 and 10 to place in array
		array[count] = randFloat(a, b);
	}
}

//display calculation totals
void displayTotals(double finaltMean, double finalpMean, double finaltVariance, 
				double finalpVariance)
{
	cout << finaltMean << " " << finalpMean << " " << finaltVariance << " " 
	<< finalpVariance << endl;
}

//generates random floating point, asks for mean and variance input
//also outputs a and b (start and end value)
double rand_mv(double mean, double var)
{
	//starting values to find
	double a, b;
	
	//finds first and end value
	b = ((2.0 * mean) + sqrt(12.0 * var)) / 2.0;
	a = ((-2.0 * mean) + sqrt(12.0 * var)) / -2.0;
	
	//(b - a) * (b - a) / 12.0 = var;
	
	//displays a and b for grading
	cout << a << " " << b << endl;
	
	//tests to see if a and b are correct
	//cout << tMean(a, b) << " " << tVariance(a, b) << endl;
	
	return randFloat(a, b);
}

int main()
{
	//random number generator
	srand (time(0));
	
	//declare user inputs for rand_mv function
	double meanInput, varianceInput;
	
	//ask for input
	cout << "Enter mean: ";
	cin >> meanInput;
	cout << endl;
	
	cout << "Enter variance ";
	cin >> varianceInput;
	cout << endl;
	
	rand_mv(meanInput, varianceInput);
	
	return 0;
}