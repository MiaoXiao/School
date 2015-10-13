#include <iostream>

using namespace std;

int main()
{
	//store default pussle
	int puzzledefault[3][3] = {{}, {}, {}};
	//store custom key
	int puzzlecustom[3][3];
	//9 is the blank spot
	int puzzlekey[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	
	int puzzletype;
	cout << "Welcome to Rica's soon to be A+ eight-puzzle solver." << endl;
	cout << "Type '1' to use default puzzle, type anything else to use custom puzzle." << endl;
	cin >> puzzletype;

	if (puzzletype == 1) //default puzzle
	{
		
	}
	else //custom puzzle
	{
		
	}
}
