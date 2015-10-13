#include <iostream>

using namespace std;

//store default pussle
int puzzledefault[3][3] = {{}, {}, {}};
//store custom key
int puzzlecustom[3][3];
//9 is the blank spot
int puzzlekey[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

//displays the custom puzzle
void displayCustomPuzzle()
{
	cout << endl;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			cout << puzzlecustom[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int puzzletype;
	cout << "Welcome to Rica's soon to be A+ eight-puzzle solver." << endl;
	cout << "Type '1' to use default puzzle, type anything else to use custom puzzle." << endl;
	cin >> puzzletype;

	if (puzzletype == 1) //default puzzle
	{
		
	}
	else //custom puzzle
	{
		int spot;
		cout << "Enter in 9 numbers, 1 - 9, seperated by spaces, which will fill in the eight puzzle." << endl;
		cout << "The eight-puzzle will be filled in from left to right, from the first row to the last row. " << endl;
		cout << "Make sure to only enter digits; entering a 9 will represent the blank space." << endl;
		cout << "No repeating digits allowed." << endl;
		for (unsigned int i = 0; i < 3; ++i)
		{
			for (unsigned int j = 0; j < 3; ++j)
			{
				cin >> spot;
				puzzlecustom[i][j] = spot;
			}
		}
		
		displayCustomPuzzle();
	}
}
