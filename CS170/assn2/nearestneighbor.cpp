#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <iomanip>
#include <fstream>

using namespace std;

int maxFeatures = 64;
int numbFeatures = 4;
int maxInstances = 2048;
int numbInstances = 0;

enum Algorithm {ForwardSelection, BackwardElimination, Ricarithm, All};

//vertex on a graph
struct Point
{
	double x;
	double y;
};

//information for a class
struct Container
{
	vector <vector<double> > features;
	vector<double> averages;
	vector<double> standarddeviations;
};

Container c1;
Container c2;

//return random number between a and b exclusive
int returnRandNumb(int a, int b)
{
	return rand() % a + b;
}

//returns distance between 2 points
double returnDistanceBetweenPoints(Point a, Point b)
{
	return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}

//assign numb of features per row
int initNumbFeatures(string filename)
{
	//open file
	ifstream f;
	f.open(filename.c_str());
	
	//check if file an be opened
	if (!f.is_open()) 
	{
		cout << "Could not read: " << filename << endl; 
		cout << "Exiting program." << endl;
		exit(1);
	}
	
	int numb = 0;
	float value;
	f >> value;
	while (!f.eof())
	{
		f >> value;
		if (value == 1 || value == 2) return numb;
		else numb++;
	}
}

//read a given file, and initalize data, averages, and standard deviations
//inint numb of instances
void readFile(string filename)
{
	//open file
	ifstream f;
	f.open(filename.c_str());
	
	//check if file an be opened
	if (!f.is_open()) 
	{
		cout << "Could not read: " << filename << endl; 
		cout << "Exiting program." << endl;
		exit(1);
	}
	
	double c;
	double value = 0;
		
	//read until end of file
	while (f >> c)
	{
		if (c != 1 && c != 2)
		{
			cout << "Not a valid class." << endl;
			exit(1);
		}
		//cout << "loop start" << endl;
		//check all features for this row until new line or end of file
		for (unsigned int i = 0; i < numbFeatures; ++i)
		{
			cout << setprecision(13);
			f >> value;
			//cout << "class: " << c << endl;
			//cout << "value: " << value << endl << endl;
			if (c == 1) //class 1
			{
				c1.features[i].push_back(value);
			}
			else if (c == 2) //class 2
			{
				c2.features[i].push_back(value);
			}
			else
			{
				cout << "Not a valid class." << endl;
				exit(1);
			}
		}
		numbInstances++;
	}
	//cout << "numbinst: " << numbInstances << endl;
	f.close();
}

//init containers/classes
void init()
{
	vector<double> t;
	for (unsigned int i = 0; i <  maxFeatures; ++i)
	{
		c1.features.push_back(t);
		c2.features.push_back(t);
	}
}

//get average of a group of elements
double average(vector<double> v)
{
	double sum = 0;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		sum += v[i];
	}
	return sum / v.size();
}

//get std deviation of a group of elements
double deviation(vector<double> v, double avg)
{
	double sum;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		sum += pow(v[i] - avg, 2);
	}
	return sqrt(sum / v.size());
}

//normalizes a value
double znormalize(double value, double mean, double standarddev)
{
	return (value - mean) / (standarddev);
}

//normalize all features from every class
void normalizeData()
{
	for (unsigned int i = 0; i < numbFeatures; ++i)
	{
		//cout << c1.features[i].size() << endl;
		//cout << c2.features[i].size() << endl;
		//get averages
		c1.averages.push_back(average(c1.features[i]));
		c2.averages.push_back(average(c2.features[i]));
		//get stddev
		c1.standarddeviations.push_back(deviation(c1.features[i], c1.averages[i]));
		c2.standarddeviations.push_back(deviation(c2.features[i], c2.averages[i]));
		for (unsigned int j = 0; j < c1.features[i].size(); ++j)
		{
			//cout << "before value: " << c1.features[i][j] << endl;
			c1.features[i][j] = znormalize(c1.features[i][j], c1.averages[i], c1.standarddeviations[i]);
			//cout << "normalized value: " << c1.features[i][j] << endl;
		}
		for (unsigned int j = 0; j < c2.features[i].size(); ++j)
		{
			//cout << "before value: " << c2.features[i][j] << endl;
			c2.features[i][j] = znormalize(c2.features[i][j], c2.averages[i], c2.standarddeviations[i]);
			//cout << "normalized value: " << c2.features[i][j] << endl;
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	string filename;
	int algorithm;
	
	init();
	//if there is any command arg, automiatically run tests
	if (argc != 1)
	{
		filename = "cs_170_small15.txt";
		algorithm = 3;
		numbFeatures = initNumbFeatures(filename);
		//cout << "nf: " << numbFeatures << endl;
		readFile(filename);
	}
	else
	{
		//Read in a file, initalize data
		cout << "Welcome to Rica Feng's Feature Selection Algorithm." << endl;
		cout << "Type in the name of the file to test: ";
		cin >> filename;
		numbFeatures = initNumbFeatures(filename);
		readFile(filename);
		
		//which algorith to use?
		cout << "Which algorithm to run? Enter a number." << endl;
		cout << "0: Forward Selection" << endl;
		cout << "1: Backward Elimination" << endl;
		cout << "2: Ricarithm" << endl; 
		cout << "3: All Algorithms" << endl; 
		cin >> algorithm;
	}
	
	cout << "This data set has " << numbFeatures << " features (not including the class attribute), with " << numbInstances << " instances. " << endl;
	cout << "Please wait while I normalize the data..." << endl;
	normalizeData();
	cout << "Done!" << endl;
}
