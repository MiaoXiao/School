#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>

using namespace std;

//store default pussle
vector<vector <int> > puzzledefault;
vector<int> puzzledefaultvalues;
//store custom key
vector<vector <int> > puzzlecustom;
//9 is the blank spot
vector<vector <int> > puzzlegoal;

//index in 2d vector
struct Index
{
		unsigned int x;
		unsigned int y;
};

//holds data about one state, and its children
struct State
{
	//current puzzle
	vector<vector<int> > puzzle;
	//index of 9
	Index blank;
	//g(n)
	int depth;
};

//initalize puzzle vectors
void initVectors()
{
	puzzledefault.reserve(3);
	puzzlecustom.reserve(3);
	for (unsigned int i = 0; i < 3; ++i)
	{
		puzzlecustom[i].reserve(3);
	}
	puzzlegoal.reserve(3);
	
	//first row
	puzzledefaultvalues.push_back(1);
	puzzledefaultvalues.push_back(3);
	puzzledefaultvalues.push_back(2);
	//second row
	puzzledefaultvalues.push_back(4);
	puzzledefaultvalues.push_back(9);
	puzzledefaultvalues.push_back(5);
	//third row
	puzzledefaultvalues.push_back(8);
	puzzledefaultvalues.push_back(6);
	puzzledefaultvalues.push_back(7);
	int spot = 0;
	int value = 1;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//cout << "spot: " << spot << endl;
			//cout << "value: " << puzzledefaultvalues[value - 1] << endl;
			puzzledefault[spot].push_back(puzzledefaultvalues[value - 1]);
			puzzlegoal[spot].push_back(value);
			value++;
		}
		spot++;
	}
}

//displays the custom puzzle
void displayCustomPuzzle(vector<vector <int> > &puzzle)
{
	//cout << "size: " << puzzle.size() << endl;
	//cout << "element: " << puzzle[0][0] << endl;
	cout << endl;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
				cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}

//checks to see if goal state is reached
bool checkGoalState()
{
	return (puzzledefault == puzzlegoal || puzzlecustom == puzzlegoal);
}

//find correct indexes of where number n piece should be
void findCorrectPos(int n, vector<vector<int> > goalstate, int &ifinal, int &jfinal)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//once correct index found, return
			if (n == goalstate[i][j])
			{
				ifinal = i;
				jfinal = j;
				return;
			}
		}
	}
}

//returns estimated cost of moving piece to correct spot
int getHeuristic(vector<vector<int> > currentstate, vector<vector<int> > goalstate)
{
	int total = 0;
	int ifinal = 0;
	int jfinal = 0;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//if spots do not match, find manhatten distance
			if (currentstate[i][j] != 9 && currentstate[i][j] != goalstate[i][j])
			{
				findCorrectPos(currentstate[i][j], goalstate, ifinal, jfinal);
				total += abs(i - ifinal) + abs(j - jfinal);
			}
		}
	}
	return total;
}


//returns false if this check is already in list
bool checkStates(vector<State> list, State check)
{
	for (unsigned int i = 0; i < list.size(); ++i)
	{
			if (list[i].puzzle == check.puzzle) return false;
	}
	return true;
}

//find possible operators
//operators: move blank (9), left, up, right, down
//return if operation is sucessful or nots
bool aStarAlgorithm(State initial)
{
	stack<State> avaliableStates;
	avaliableStates.push(initial);
	
	//check this to see which states have already been traversed
	vector<State> doneStates;
	
	while (!avaliableStates.empty())
	{
		State checking = avaliableStates.top();
		
		int temp;
		//check operation moving 9 down
		if (checking.blank.x != 2)
		{
			State next = avaliableStates.top();
			
			//swap elements
			next.puzzle[next.blank.x][next.blank.y] = next.puzzle[next.blank.x + 1][next.blank.y];
			next.blank.x++;
			
			//only add state if it has not been searched before
			if (checkStates(doneStates, next))
			{
				avaliableStates.push(next);
				doneStates.push_back(next);
			}
		}
		//check operation moving 9 right
		if (checking.blank.y != 2)
		{
			State next = avaliableStates.top();
			
			//swap elements
			next.puzzle[next.blank.x][next.blank.y] = next.puzzle[next.blank.x][next.blank.y + 1];
			next.blank.y++;
			
			//only add state if it has not been searched before
			if (checkStates(doneStates, next))
			{
				avaliableStates.push(next);
				doneStates.push_back(next);
			}
		}
		//check operation moving 9 up
		if (checking.blank.x != 0)
		{
			State next = avaliableStates.top();
			
			//swap elements
			next.puzzle[next.blank.x][next.blank.y] = next.puzzle[next.blank.x - 1][next.blank.y];
			next.blank.x--;
			
			//only add state if it has not been searched before
			if (checkStates(doneStates, next))
			{
				avaliableStates.push(next);
				doneStates.push_back(next);
			}
		}
		//check operation moving 9 left
		if (checking.blank.y != 0)
		{
			State next = avaliableStates.top();
			
			//swap elements
			next.puzzle[next.blank.x][next.blank.y] = next.puzzle[next.blank.x][next.blank.y - 1];
			next.blank.y--;
			
			//only add state if it has not been searched before
			if (checkStates(doneStates, next))
			{
				avaliableStates.push(next);
				doneStates.push_back(next);
			}
		}
		avaliableStates.pop();
	}
}

int main()
{
	State initial;
	//init vectors
	initVectors();
	
	int puzzletype;
	cout << "Welcome to Rica's soon to be A+ eight-puzzle solver." << endl;
	cout << "Type '1' to use default puzzle, type anything else to use custom puzzle." << endl;
	cin >> puzzletype;

	if (puzzletype == 1) //default puzzle
	{
		initial.puzzle = puzzledefault;
		initial.blank.y = 1;
		initial.blank.y = 1;
		initial.depth = 0;
		
		aStarAlgorithm(initial);
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
				if (spot == 9)
				{
					initial.blank.x = i;
					initial.blank.y = j;
				}
				puzzlecustom[i][j] = spot;
			}
		}

		initial.puzzle = puzzlecustom;
		initial.depth = 0;
		aStarAlgorithm(initial);
		
		//cout << "element: " << puzzledefault[0][0] << endl;
		//displayCustomPuzzle(puzzledefault);
		//displayCustomPuzzle(puzzlecustom);
		//displayCustomPuzzle(puzzlegoal);
		
		//cout << "curr h: " << getHeuristic(puzzlecustom, puzzlegoal) << endl;
	}
}
