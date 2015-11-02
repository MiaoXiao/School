#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <queue>
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
	State() 
	{
		parent = -1;
		pos = 0;
		message = "Initital state.";
	}
	//current puzzle
	vector<vector<int> > puzzle;
	//index of 9
	Index blank;
	
	//g(n)
	int depth;
	//f(n)
	int manhatten;
	//total hearuestic
	int total;
	
	//movement message
	string message;
	
	//this state's position in tree
	int pos;
	//parent of next state (for calculating answer path)
	int parent;
	
	//swap two elements in puzzle
	void swap(int x1, int y1, int x2, int y2)
	{
		int temp = puzzle[x1][y1];
		puzzle[x1][y1] = puzzle[x2][y2];
		puzzle[x2][y2] = temp;
	}
};

//holds all possible states
struct Tree
{
	vector<State> list;
};

//displays an 8 puzzle
void displayPuzzle(vector<vector<int> > s)
{
	//cout << "size: " << s.size() << endl;
	//cout << "element: " << s[0][0] << endl;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
				cout << s[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//initalize puzzle vectors
void initVectors()
{
	vector<int> v;
	
	for (unsigned int i = 0; i < 3; ++i)
	{
		puzzledefault.push_back(v);
		puzzlecustom.push_back(v);
		puzzlegoal.push_back(v);
	}
	
	//first row
	puzzledefaultvalues.push_back(1);
	puzzledefaultvalues.push_back(9);
	puzzledefaultvalues.push_back(3);
	//second row
	puzzledefaultvalues.push_back(4);
	puzzledefaultvalues.push_back(2);
	puzzledefaultvalues.push_back(5);
	//third row
	puzzledefaultvalues.push_back(7);
	puzzledefaultvalues.push_back(8);
	puzzledefaultvalues.push_back(6);
	
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
	//displayPuzzle(puzzledefault);
	//displayPuzzle(puzzlecustom);
	//displayPuzzle(puzzlegoal);
}

//checks to see if goal state is reached
bool checkGoalState(vector<vector<int> > s)
{
	return (s == puzzlegoal);
}

//find correct indexes of where number n piece should be
void findCorrectPos(int n, int &ifinal, int &jfinal)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//once correct index found, return
			if (n == puzzlegoal[i][j])
			{
				ifinal = i;
				jfinal = j;
				return;
			}
		}
	}
}

//returns estimated cost of moving piece to correct spot using manhatten distance
int manhattenHeuristic(vector<vector<int> > currentstate)
{
	int total = 0;
	int ifinal = 0;
	int jfinal = 0;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//if spots do not match, find manhatten distance
			if (currentstate[i][j] != 9 && currentstate[i][j] != puzzlegoal[i][j])
			{
				findCorrectPos(currentstate[i][j], ifinal, jfinal);
				total += abs(i - ifinal) + abs(j - jfinal);
			}
		}
	}
	return total;
}

//returns false if this check is already in list
bool checkStates(vector<State> list, vector<vector<int> > check)
{
	for (unsigned int i = 0; i < list.size(); ++i)
	{
		/*
		cout << "comparing: " << endl;
		displayPuzzle(list[i].puzzle);
		cout << "to:" << endl;
		displayPuzzle(check); */
		for (unsigned int j = 0; j < 3; ++j)
		{
			for (unsigned int k = 0; k < 3; ++k)
			{
				cout << "comparing" << list[i].puzzle[j][k] << " and " << check[j][k] << endl;
				if (list[i].puzzle[j][k] != check[j][k]) return true;
			}
		}
	}
	return false;
}

/*
//comparotor for priority queue
struct OrderBySmallestHeurestic
{
    bool operator() (State const &a, State const &b) { return a.heauristic < b.heauristic; }
};*/

//check if puzzle is even possible
bool checkPossible(vector<vector<int > > p)
{
	//put 2d vector into just 1 vector
	vector<int> straight;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			straight.push_back(p[i][j]);
		}
	}
	//compare every element with the elements in front, to check for inversions
	int numbOfInversions = 0;
	for (int i = 0; i < straight.size(); ++i)
	{
		for (unsigned int j = i + 1; j < straight.size(); ++j)
		{
			if (straight[i] != 9 && straight[j] != 9 &&
				straight[j] > straight[i]) 
			{
				numbOfInversions++;
			}
		}
	}
	cout << "Numb of inversions: " << numbOfInversions << endl;
	//if inversions are even, puzzle is solvable
	if (numbOfInversions % 2 == 0) return true;
	return false;
}

//uniform cost search. returns true if success, returns false if impossible
bool uniformCostSearch(State initial)
{
	//check if initial state is goal
	if (checkGoalState(initial.puzzle)) return true;
	//check if puzzle is even possible
	if (!checkPossible(initial.puzzle)) return false;
	
	//tree
	Tree tree;
	//push first state
	tree.list.push_back(initial);
	
	//push all valid states. push initial state. pop queue to check
	queue<State> avaliableStates;
	avaliableStates.push(initial);
	
	//set to true when puzzle is solved
	bool puzzleSolved = false;
	
	while (!avaliableStates.empty())
	{
		//recurse back up the tree when puzzle is solved
		if (puzzleSolved)
		{
			//put reversed path in stack, to correct the order
			int nextIndex = tree.list.size() - 1;
			stack<State> temp;
			while (nextIndex != -1)
			{
				temp.push(tree.list[nextIndex]);
				nextIndex = tree.list[nextIndex].parent;
			}
			//displayc correct path to puzzle
			for (unsigned int i = 1; !temp.empty(); ++i)
			{
				cout << i << ": " << endl;
				cout << temp.top().message << endl;
				displayPuzzle(temp.top().puzzle);
				temp.pop();
			}
			return true;
		}
		//check this state and see what operations are possible
		State checking = avaliableStates.front();
		avaliableStates.pop();
		
		//cout << "Currently checking: " << endl;
		//displayPuzzle(checking.puzzle);
		//check operation moving 9 left
		if (checking.blank.y != 0)
		{
			State next = checking;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x, next.blank.y - 1);
			next.blank.y--;
			
			next.message = "Moved blank left.";
			
			next.parent = checking.pos;
			tree.list.push_back(next);
			next.pos = tree.list.size() - 1;
			avaliableStates.push(next);
			if (checkGoalState(next.puzzle)) puzzleSolved = true;
		}
		//check operation moving 9 up
		if (!puzzleSolved && checking.blank.x != 0)
		{
			State next = checking;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x - 1, next.blank.y);
			next.blank.x--;
			
			next.message = "Moved blank up.";
			
			next.parent = checking.pos;
			tree.list.push_back(next);
			next.pos = tree.list.size() - 1;
			avaliableStates.push(next);
			if (checkGoalState(next.puzzle)) puzzleSolved = true;
		}
		//check operation moving 9 right
		if (!puzzleSolved && checking.blank.y != 2)
		{
			State next = checking;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x, next.blank.y + 1);
			next.blank.y++;
			
			next.message = "Moved blank right.";
			
			next.parent = checking.pos;
			tree.list.push_back(next);
			next.pos = tree.list.size() - 1;
			avaliableStates.push(next);
			if (checkGoalState(next.puzzle)) puzzleSolved = true;
		}
		//check operation moving 9 down
		if (!puzzleSolved && checking.blank.x != 2)
		{
			State next = checking;
			
			//swap elements
			next.swap(next.blank.x, next.blank.y, next.blank.x + 1, next.blank.y);
			next.blank.x++;
			
			next.message = "Moved blank down.";
			
			next.parent = checking.pos;
			tree.list.push_back(next);
			next.pos = tree.list.size() - 1;
			avaliableStates.push(next);
			if (checkGoalState(next.puzzle)) puzzleSolved = true;
		}
	}
	return false;
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
		initial.blank.x = 0;
		initial.blank.y = 1;
		initial.depth = 0;
		
		//displayPuzzle(initial.puzzle);
		//displayPuzzle(puzzlegoal);
		
		if (uniformCostSearch(initial)) cout << "Puzzle solved." << endl;
		else cout << "Puzzle is impossible to solve." << endl;
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
		uniformCostSearch(initial);
	
	}
}
