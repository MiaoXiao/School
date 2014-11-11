#include <iostream>
#include <ios>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

//Basic algorithm 
/*
1. Get from the user the names of the input and output files.

2. Read from the input file the initial temps for top, right, bottom, and left 
	sides of plate.

3. Read from the input file the tolerance for equilibrium.

4. Initialize the edges of the 2D grid with initial temps you got from the 
	input file, and initialize the inner cells of the grid to 0.0.

5. Continue updating temperature values within inner cells until equilibrium is 
	reached.

6. Output to the output file the values of the inner cells of the grid after 
	equilibrium obtained.
*/

//reads all grid side values and tolerance into their variables
void readVar(double& top, double& right, double& bottom, double& left, 
			  double& tolerance, string streamFile)
{
	//init and open stream
	ifstream temp;
	temp.open(streamFile.c_str());
	
	//check if file is opened correctly
	 if (!temp.is_open()) 
	{
		cout << "Could not open file" << endl;
	}
	
	//read in variables
	temp >> top >> right >> bottom >> left >> tolerance;
	
	//end stream
	temp.close();
}

//initilize grids side values and and tolerance, also assigns 0.0 to remaining
	//grid values
void initGrid(double grid[][8], double top, double right, double bottom, 
			   double left)
{
	for (int j = 0; j < 8; j++)
	{
		grid[0][j] = top;
		grid[5][j] = bottom;
	}
	for (int i = 1; i < 5; i++)
	{
		grid[i][0] = left;
		grid[i][7] = right;
	}
}

//Displays 2d grid with all its current values
void displayGrid (double grid[][8])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << left << setw(16) << grid[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

//checks all around 1 element in grid and returns the average. 
	//used in updateGrid
double averageGrid(double grid[][8], int rows, int columns)
{
	//positions relative to the element in question
	double left, right, up, down;
	
	left = grid[rows][columns - 1];
	right = grid[rows][columns + 1];
	up = grid[rows - 1][columns];
	down = grid[rows + 1][columns];
	
	return (left + right + up + down) / 4;
}

//update every element of grid except the sides. (every element should be an
	//average of the elements around it
	//also returns the max difference in the update cycle
double updateGrid(double grid[][8])
{
	//holds old value of cell before updating it
	double oldValue;
	//difference between new and old value
	double difference;
	//highest difference so far
	double max = 0.0;
	
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 7; j++)
		{
			//assigns grid value to placeholder
			oldValue = grid[i][j];
			//updates cell with the average temp
			grid[i][j] = averageGrid(grid, i, j);
			
			//calculates difference and makes sure it is always +
			difference = abs(oldValue - grid[i][j]);
			
			//assigns new max if difference is the largest so far
			if (difference > max)
			{
				max = difference;
			}
		}
	}
	//displayGrid(grid);
	//test max/min
	//cout << "Max: " << endl << max << endl;
	return max;
}

//check if equilibrium is reached( max and the min distance is less than the
	//tolerance
bool isEquilibrium(double max, double tolerance)
{
	if (max <= tolerance)
	{
		return false;
	}
	return true;
}

//inserts final grid into file
void insertOutput(double grid[][8], string outputfileName)
{
	//init output file
	ofstream output;
	output.open(outputfileName.c_str());
	
	//check if file is opened correctly
	if (!output.is_open()) 
	{
		cout << "Could not open file" << endl;
	}
	
	//outputs all values of grid into putput
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 7; j++)
		{
			output << left << setw(16) << grid[i][j];
		}
		output << endl;
	}
	
	//closes output
	output.close();
}

int main()
{
	//files that hold values for grid and the tolerance, and the final output
	string inputfileName, outputfileName;
	//variables for initial temperatures for all sides of the grid
	double top = 0.0, right = 0.0, bottom = 0.0, left = 0.0;
	//variable for tolerance; how much the max temp and the min temp can differ
	double tolerance = 0.0;
	//temporary variables that will hold the max difference of
		//temperature so far
	double max;
	
	//init 6 X 8 grid size and every element to 0
	double grid[6][8] = {0.0};
	
	//ask and aquire input file name
	cout << "What is the input file?: ";
	cin >> inputfileName;
	cout << endl;

	//ask and aquire input file name
	cout << "What is the output file?: ";
	cin >> outputfileName;
	cout << endl;
	
	//reads variables from file 
	readVar(top, right, bottom, left, tolerance, inputfileName);
	
	//test to see if variables are input correctly
	//cout << "Grid Sizes: " 
	//<< top << " " << right << " " << bottom << " " << left << endl 
	//<< "Tolerance: " << tolerance << endl;
	
	//initalize grid with correct temperatures
	initGrid(grid, top, right, bottom, left);
	
	//display grid and all its current values
	//displayGrid(grid);
	
	//constantly updates grid until check until equilibrium is reached
	do
	{
		max = updateGrid(grid);
	} while(isEquilibrium(max, tolerance));
	
	//test max/min
	//cout << "Max: " << endl << max << endl;
	
	//finish updating, outputs temperatures to file
	insertOutput(grid, outputfileName);
	
	return 0;
}