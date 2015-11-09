#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <fstream>

using namespace std;

enum Algorithm {ForwardSelection, BackwardElimination, Ricarithm, All};

//read a given file, and initalize data
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
}

int main(int argc, char *argv[])
{
	string filename;
	int algorithm;
	
	//if there is any command arg, automiatically run tests
	if (argc != 1)
	{
		filename = "defaultdata.txt";
		algorithm = 3;
	}
	else
	{
		//Read in a file, initalize data
		cout << "Welcome to Rica Feng's Feature Selection Algorithm." << endl;
		cout << "Type in the name of the file to test: ";
		cin >> filename;
		readFile(filename);
		
		//which algorith to use?
		cout << "Which algorithm to run? Enter a number." << endl;
		cout << "0: Forward Selection" << endl;
		cout << "1: Backward Elimination" << endl;
		cout << "2: Ricarithm" << endl; 
		cout << "3: All Algorithms" << endl; 
	}
}
