#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//arrays for storing doubles
double smallArray[500];
double largeArray[500];

//global constants to define ranges for number generator
const double SMALLA = 2.775,SMALLB = 5.225;
const double LARGEA = 1.55,LARGEB = 6.45;

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

int main()
{
	//random number generator
	srand (time(0));
	
	//declare variables for:
		//thearetical mean, practical mean, 
		//thearetical variance, practical variance
	double finaltMean, finalpMean, finaltVariance, finalpVariance;
	
	//fill small array and large array (size 500 and 500) with random floats
	fillArray(smallArray, 500, SMALLA, SMALLB);
	fillArray(largeArray, 500, LARGEA, LARGEB);
	
	//calculate means and variances for array of 500
	finaltMean = tMean(SMALLA, SMALLB);
	finalpMean = pMean(smallArray, 500);
	finaltVariance = tVariance(SMALLA, SMALLB);
	finalpVariance = pVariance(smallArray, 500, finalpMean);
	
	//display means and variances for array of 500
	displayTotals(finaltMean, finalpMean, finaltVariance, finalpVariance);
	
	//calculate means and variances for second array of 500
	finaltMean = tMean(LARGEA, LARGEB);
	finalpMean = pMean(largeArray, 500);
	finaltVariance = tVariance(LARGEA, LARGEB);
	finalpVariance = pVariance(largeArray, 500, finalpMean);
	
	//display means and variances for second array of 500
	displayTotals(finaltMean, finalpMean, finaltVariance, finalpVariance);
	
	return 0;
}