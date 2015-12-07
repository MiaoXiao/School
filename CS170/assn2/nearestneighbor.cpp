#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h> 
#include <queue>
#include <utility>
#include <iomanip>
#include <fstream>

using namespace std;

//check this number of nearest k neghbors
#define NEARESTK 3

//features
const int maxFeatures = 64;
int numbFeatures = 0;

//instances (rows)
const int maxInstances = 2048;
int c1Instances = 0;
int c2Instances = 0;
int numbInstances = 0;

//subdivision
int K = 1;

double average = 0;
double standarddev = 0;

enum Algorithm {ForwardSelection, BackwardElimination, Ricarithm, All};

//point on a graph
struct Point
{
	Point(vector<double> c)
		: coordinates(c) {}
	vector<double> coordinates;
};

//stores points
struct Graph
{
	vector<pair<int, Point> > points;
};

//information for a class
struct Container
{
	vector <vector<double> > features;
};

//only 2 classes
Container c1;
Container c2;

//return random number between a and b exclusive
int returnRandNumb(int a, int b)
{
	return rand() % a + b;
}

//returns distance between two points
//given list of all features to test and index
double returnDistance(vector<double> a, vector<double> b)
{
	double sum = 0;
	for (unsigned int i = 0; i < a.size(); ++i)
	{
		//cout << "i: " << i << endl;
		sum += pow(a[i] - b[i], 2);
	}
	return sqrt(sum);
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

//get std deviation of all elements
double deviation(vector<double> v)
{
	double sum = 0;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		sum += pow(v[i] - average, 2);
	}
	return sqrt(sum / v.size());
}

//read a given file, and initalize data, averages, and standard deviations
//inint numb of instances
void readFile(string filename)
{
	//holds all values
	vector<double> allValues;
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
			cout << setprecision(20);
			f >> value;
			average += value;
			allValues.push_back(value);
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
		if (c == 1) c1Instances++;
		else c2Instances++;
	}
	//cout << "numbinst: " << numbInstances << endl;
	f.close();
	//get final average
	average /= allValues.size();
	//get final standard deviation
	standarddev = deviation(allValues);
}

//init containers/classes
void initFeatures()
{
	vector<double> t;
	for (unsigned int i = 0; i <  numbFeatures; ++i)
	{
		c1.features.push_back(t);
		c2.features.push_back(t);
	}
}

//normalizes a value
double znormalize(double value)
{
	return (value - average) / (standarddev);
}

//normalize all features from every class
void normalizeData()
{
	for (unsigned int i = 0; i < numbFeatures; ++i)
	{
		//cout << c1.features[i].size() << endl;
		//cout << c2.features[i].size() << endl;
		
		//normalize each data value for that feature
		for (unsigned int j = 0; j < c1.features[i].size(); ++j)
		{
			//cout << "before value: " << c1.features[i][j] << endl;
			c1.features[i][j] = znormalize(c1.features[i][j]);
			//cout << "normalized value: " << c1.features[i][j] << endl;
		}
		for (unsigned int j = 0; j < c2.features[i].size(); ++j)
		{
			//cout << "before value: " << c2.features[i][j] << endl;
			c2.features[i][j] = znormalize(c2.features[i][j]);
			//cout << "normalized value: " << c2.features[i][j] << endl;
		}
	}
}

//for priority queue
struct Compare
{
	bool operator()(const pair<int, double>& lhs, const pair<int, double>& rhs)
	{
		return lhs.second > rhs.second;
	}
};

//returns accuracy
//k = size of subdivision
//f is a vector of all features to test
double leaveOneOutEvaluation(int k, vector<int> f)
{
	//create graph with all relevant features
	Graph g;
	//add all c1 points
	for (unsigned int i = 0; i < c1Instances; ++i)
	{
		vector<double> c1coord;
		for (unsigned int j = 0; j < f.size(); ++j)
		{
			//cout << "class 1: " << c1.features[f[j]][i] << endl;
			c1coord.push_back(c1.features[f[j]][i]);
		}
		Point p1(c1coord);
		g.points.push_back(make_pair(1, p1));
	}
	//add all c2 points
	for (unsigned int i = 0; i < c2Instances; ++i)
	{
		vector<double> c2coord;
		for (unsigned int j = 0; j < f.size(); ++j)
		{
			//cout << "class 2: " << c2.features[f[j]][i] << endl;
			c2coord.push_back(c2.features[f[j]][i]);
		}
		Point p2(c2coord);
		g.points.push_back(make_pair(2, p2));
	}	
	//shuffle all coordinates in graph
	random_shuffle(g.points.begin(), g.points.end());
	
	//starting testcase (subdivision)
	int minindex = 0;
	int maxindex = k - 1;
	
	//number of times correct
	double numbCorrect = 0;
	
	//loop until every combination of test/train casees tested
	while (maxindex < numbInstances)
	{
		//cout << "minindex: " << minindex << endl;
		//cout << "maxindex: " << maxindex << endl;
		//loop through all valid points to find closest point to current point
		for (unsigned int i = minindex; i <= maxindex; ++i)
		{
			//cout << "begin check" << endl;
			//automatically sorts points by smallest distance to largest
			priority_queue<pair<int, double>, vector<pair<int, double> >, Compare > closelist;
			for (unsigned int j = 0; j < numbInstances; ++j)
			{
				//check to make sure the point we are comparing to is not already in the test set
				if (j <= minindex || j > maxindex)
				{
					//cout << j << endl;
					//check if this point is closest;
					double distance = returnDistance(g.points[i].second.coordinates, g.points[j].second.coordinates);
					closelist.push(make_pair(g.points[j].first, distance));
				}
			}
			//determine if this point matches the correct class by comparing the point to the
			//kth - 1 smallest elements,
			int correct = 0;
			int incorrect = 0;
			for (unsigned int j = 0; j < NEARESTK; ++j)
			{
				//cout << "check distance: " << closelist.top().second << endl;
				if (closelist.top().first == g.points[i].first) correct++;
				else incorrect++;
				closelist.pop();
			}
			//cout << "c: " << correct << endl;
			//cout << "ic: " << incorrect << endl;
			if (correct > incorrect) numbCorrect++;
		}
		//move test set
		minindex += k;
		maxindex += k;
	}
	//cout << "correct: " << numbCorrect << endl;
	return numbCorrect / numbInstances;
}

//displays set of numbers
void displaySet(vector<int> v)
{
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		cout << v[i] + 1;
		if (i != v.size() - 1) cout << ", ";
	}
}

//start with no features, add the feature that increases accuracy the most
//if using ricarithm, ban the feature that decreases accuracy the most
void forwardSelection(bool ricarithm)
{
	//vector for testing current features
	vector<int> testfeatures;
	vector<int> bestfeatures;
	
	//IF RICARITHM
	//fill vector with banned features
	vector<int> banList;
	//keep track of lowest percent and corresponding feature
	double lowPercent;
	double lowFeature;
	
	//current percentage
	double currpercentage;
	//best percentage for this set of features
	double bestpercentage;
	//feature number of best
	double bestfeatureIndex;
	
	//temporarily store current run's temp percentage
	double temppercentage;
	double tempIndex;
	
	//if we are at an invalid feature, set to false
	bool keepfeature = true;
	//flag to check if we should stop algorthm earlier
	bool done = false;
	
	//set to true if new best feature was found
	bool better_feature_found = false;

	cout << "Beginning Search." << endl;
	for (unsigned int x = 0; x < numbFeatures && !done; ++x)
	{
		better_feature_found = false;
		currpercentage = 0;
		tempIndex = 0;
		temppercentage = 0;
		lowPercent = 100;
		lowFeature = -1;
		
		//check next best feature to add in
		for (unsigned int i = 0; i < numbFeatures; ++i)
		{
			keepfeature = true;
			//check to see if we already have this feature, or if this feature is banned
			for (unsigned int j = 0; j < testfeatures.size(); ++j)
			{
				if (testfeatures[j] == i) keepfeature = false;
				for (unsigned k = 0; ricarithm && k < banList.size() && keepfeature; ++k)
				{
					if (banList[k] == i) keepfeature = false;
				}
			}
			//only check accuracy if we did not check this feature yet
			if (keepfeature)
			{
				testfeatures.push_back(i);
				
				cout << "\tUsing feature(s) {";
				displaySet(testfeatures);
				cout << "} accuracy is ";
				currpercentage = leaveOneOutEvaluation(K, testfeatures);
				cout << currpercentage * 100.0 << "%" << endl;
				
				
				//check if lowest percentage, for ricarithm
				if (ricarithm && currpercentage < lowPercent)
				{
					lowPercent = currpercentage;
					lowFeature = i;
				}
				if (currpercentage > bestpercentage)
				{
					better_feature_found = true;
					
					temppercentage = currpercentage;
					tempIndex = i;		
					
					bestpercentage = currpercentage;
					bestfeatureIndex = testfeatures[testfeatures.size() - 1];
					bestfeatures = testfeatures;
				}
				if (currpercentage > temppercentage)
				{
					temppercentage = currpercentage;
					tempIndex = i;					
				}
				testfeatures.pop_back();
			}
		}
		testfeatures.push_back(tempIndex);
		
		cout << endl;
		//if no best feature was found, finish searching
		if (!better_feature_found)
		{
			cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			//done = true;
		}
		cout << "Feature set {";
		displaySet(testfeatures);
		cout << "} was best, accuracy is " << temppercentage * 100.0 << "%" << endl;
		
		//add lowest percentile feature to banlist
		if (ricarithm)
		{
			banList.push_back(lowFeature);
			cout << "Banning feature(s): {";
			displaySet(banList);
			cout << "} on the next search." << endl;
			//if banlist size is equal to half the numb of features, we are done
			if (banList.size() >= (numbFeatures - 1) / 2) done = true; 
		}
		cout << endl;	
	}
	cout << "Finished search!! The best feature subset is {";
	displaySet(bestfeatures);
	cout << "}, which has an accuracy of " << bestpercentage * 100.0 << "%" << endl;
}

//start with all features, remove the feature that increases accuracy the most
void backwardElimination()
{
	//vector for testing current features
	vector<int> testfeatures;
	for (unsigned int i = 0; i < numbFeatures; ++i)
	{
		testfeatures.push_back(i);
	}
		
	//current percentage
	double currpercentage;
	
	vector<int> bestfeatures;
	//best percentage for this set of features
	double bestpercentage;
	//feature number of best
	double bestfeatureIndex;
	
	//vector for keeping track of best features
	vector<int> answer;
	//best overall percentage
	double answerpercentage = leaveOneOutEvaluation(K, testfeatures);
	
	bool done = false;
	
	cout << "Beginning Search." << endl;
	
	cout << "\tUsing ALL feature(s) {";
	displaySet(testfeatures);
	cout << "} accuracy is " << answerpercentage * 100.0 << "%" << endl;
	
	while (testfeatures.size() != 1 && !done)
	{
		bestpercentage = 0;
		bestfeatureIndex = 0;
		currpercentage = 0;
		
		//check next best feature to add in
		for (unsigned int i = 0; i < testfeatures.size(); ++i)
		{
			//cout << "Removing Element: " << testfeatures[i] << endl;
			//erase the ith element, then test that
			double saveValue = testfeatures[i];
			testfeatures.erase(testfeatures.begin() + i);
			
			cout << "\tUsing feature(s) {";
			displaySet(testfeatures);
			cout << "} accuracy is ";
			
			currpercentage = leaveOneOutEvaluation(K, testfeatures);
			cout << currpercentage * 100.0 << "%" << endl;
			if (currpercentage > bestpercentage)
			{
				bestpercentage = currpercentage;
				bestfeatureIndex = i;
				bestfeatures = testfeatures;
			}
			
			//add the element back on, then sort again
			//cout << "Adding Element" << saveValue << endl;
			testfeatures.push_back(saveValue);
			sort(testfeatures.begin(), testfeatures.end());
			//cout << "sdf" << endl;
		}
		
		cout << endl;
		//cout << "best fe in: " << bestfeatureIndex << endl;
		//remove the element that will increase accuracy the most
		testfeatures.erase(testfeatures.begin() + bestfeatureIndex);
		if (bestpercentage > answerpercentage)
		{
			answer = bestfeatures;
			answerpercentage = bestpercentage;
		}
		else
		{
			cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			//done = false;
		}
		cout << "Feature set {";
		displaySet(bestfeatures);
		cout << "} was best, accuracy is " << bestpercentage * 100.0 << "%" << endl << endl;
	}
	cout << "Finished search!! The best feature subset is {";
	displaySet(answer);
	cout << "}, which has an accuracy of " << answerpercentage * 100.0 << "%" << endl;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	string filename;
	int algorithm;
	
	//if there is any command arg, automiatically run tests
	if (argc != 1)
	{
		filename = "cs_170_small80.txt";
		
		cout << *argv[1] << endl;
		//choose algorithm
		if(*argv[1] == '1') algorithm = 0;
		else if (*argv[1] == '2') algorithm = 1;
		else algorithm = 2;
		
		numbFeatures = initNumbFeatures(filename);
		initFeatures();
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
		initFeatures();
		readFile(filename);
		
		//which algorith to use?
		cout << "Which algorithm to run? Enter a number." << endl;
		cout << "0: Forward Selection" << endl;
		cout << "1: Backward Elimination" << endl;
		cout << "2: Ricarithm" << endl; 
		cin >> algorithm;
		if (algorithm < 0 || algorithm > 2)
		{
			cout << "Not a valid algorithm." << endl;
			exit(1);
		}
	}
	
	cout << "This data set has " << numbFeatures << " features (not including the class attribute), with " << numbInstances << " instances. " << endl << endl;
	cout << "Please wait while I normalize the data...";
	normalizeData();
	cout << "Done!" << endl << endl;
	
	//choose specified algorithm, or run all algorithms
	switch (algorithm)
	{
		case ForwardSelection:
			forwardSelection(false);
			break;
		case BackwardElimination:
			backwardElimination();
			break;
		case Ricarithm:
			forwardSelection(true);
			break;
	}
}
